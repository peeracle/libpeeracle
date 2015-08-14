/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include <algorithm>
#include <string>
#include <iostream>

#include "peeracle/Tracker/Client/WebSocketsClient.h"
#include "peeracle/Tracker/Message/TrackerMessage.h"
#include "peeracle/DataStream/MemoryDataStream.h"

namespace peeracle {

static const std::string prclProtocol = "prcl-0.0.1";

int WebSocketsClient::Callback(
  struct libwebsocket_context *context, struct libwebsocket *wsi,
  enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
  Userdata *userData =
    reinterpret_cast<Userdata *>(user);

  WebSocketsClient *client = NULL;
  unsigned char *buffer = NULL;

  if (userData) {
    client = userData->client;
    buffer = userData->buffer;
  }

  switch (reason) {
    case LWS_CALLBACK_CLOSED: {
      if (!userData) {
        break;
      }
      client->_observer->onDisconnect();
      break;
    }

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
      if (!userData) {
        break;
      }

      client->_observer->onError();
      return -1;
    }

    case LWS_CALLBACK_CLIENT_ESTABLISHED: {
      if (!userData) {
        break;
      }

      /*TrackerMessageInterface *msg =
        new TrackerMessage(TrackerMessageInterface::kHello);
      client->_messages.push(msg);*/

      client->_observer->onConnect();
      lwsl_notice("Client has connected\n");
      break;
    }

    case LWS_CALLBACK_CLIENT_RECEIVE: {
      if (!userData) {
        break;
      }

      client->_observer->onMessage(reinterpret_cast<char *>(in), len);
      break;
    }

      /*case LWS_CALLBACK_CLIENT_RECEIVE: {
        int type;

        if (!userData) {
          break;
        }

        DataStreamInit dsInit;
        MemoryDataStream *dataStream = new MemoryDataStream(dsInit);
        TrackerMessageInterface *message = new TrackerMessage();

        dataStream->write(reinterpret_cast<char *>(in), len);
        dataStream->seek(0);
        message->unserialize(dataStream);

        type = message->getType();
        std::cout << "Got message type " << static_cast<int>(type) << std::endl;
        switch (type) {
          case TrackerMessageInterface::kWelcome:
          {
            std::string id;

            message->get("id", &id, "");

            client->_observer->onConnect();
          }
          case TrackerMessageInterface::kPoke:
          {
            std::string hash;
            std::string peer;
            uint32_t got;

            message->get("hash", &hash, "");
            message->get("peer", &peer, "");
            message->get("got", &got, 0);

            client->_observer->onPeerConnect(hash, peer, got, true);
          }
          default:
            break;
        }
        break;
      }*/

    case LWS_CALLBACK_CLIENT_WRITEABLE: {
      if (!userData || client->_messages.empty()) {
        break;
      }

      int n;
      Message *message = client->_messages.front();

      memcpy(&buffer[LWS_SEND_BUFFER_PRE_PADDING], message->buffer,
             message->length);

      n = libwebsocket_write(wsi, &buffer[LWS_SEND_BUFFER_PRE_PADDING],
                             static_cast<size_t>(message->length),
                             LWS_WRITE_BINARY);

      client->_messages.pop();

      delete message->buffer;
      delete message;

      if (n < 0) {
        lwsl_err("ERROR %d writing to socket, hanging up\n", n);
        return -1;
      }

      if (n < static_cast<int>(message->length)) {
        lwsl_err("Partial write\n");
        return -1;
      }

      break;
    }
    case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: {
      break;
    }
    default:
      break;
  }

  return 0;
}

WebSocketsClient::WebSocketsClient(const std::string &url,
                                   WebSocketsClientObserver *observer) :
  _url(url), _observer(observer) {
#ifdef _DEBUG
  lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG |
                    LLL_HEADER, NULL);
#endif
}

bool WebSocketsClient::Init() {
  struct lws_context_creation_info info;

  memset(&info, 0, sizeof info);

  info.port = CONTEXT_PORT_NO_LISTEN;
  // info.iface = interface;
  _protocols = new libwebsocket_protocols[2];
  _protocols[0].name = prclProtocol.c_str();
  _protocols[0].callback = Callback;
  _protocols[0].per_session_data_size = sizeof(struct Userdata);

  _protocols[1].name = NULL;
  _protocols[1].callback = NULL;
  _protocols[1].per_session_data_size = 0;

  info.protocols = _protocols;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = 0;

  _context = libwebsocket_create_context(&info);
  if (_context == NULL) {
    lwsl_err("libwebsocket init failed\n");
    return false;
  }

  lwsl_info("libwebsocket init success\n");
  return true;
}

bool WebSocketsClient::Connect() {
  char uri[256] = "/";
  int use_ssl = 0;
  std::string host;
  std::string protocol;
  uint16_t port;
  std::stringstream portstr;
  std::stringstream ads_port;

  if (!_context) {
    return false;
  }

  std::string::const_iterator protocolIt = std::find(_url.begin(),
                                                     _url.end(), ':');
  if (protocolIt == _url.end()) {
    return false;
  }

  std::string protocolPtr = &*(protocolIt);
  if ((protocolPtr.length() > 3) && (protocolPtr.substr(0, 3) == "://")) {
    protocol = std::string(_url.begin(), protocolIt);
    lwsl_info("protocol = {%s}\n", protocol.c_str());

    if (protocol != "ws" && protocol != "wss") {
      return false;
    }

    if (protocol == "wss") {
      use_ssl = 1;
    }

    protocolIt += 3;
  }

  std::string::const_iterator hostIt = std::find(protocolIt, _url.end(), ':');

  if (hostIt == _url.end()) {
    return false;
  }

  host = std::string(protocolIt, hostIt);
  hostIt += 1;

  portstr << std::string(hostIt, _url.end());
  portstr >> port;

  ads_port << host << ":" << port;
  lwsl_info("ads = {%s}\n", ads_port.str().c_str());

  _userData.client = this;
  _wsi = libwebsocket_client_connect_extended(_context, host.c_str(),
                                              port, use_ssl, uri,
                                              ads_port.str().c_str(),
                                              ads_port.str().c_str(),
                                              "prcl-0.0.1", -1,
                                              &_userData);

  if (!_wsi) {
    lwsl_err("Client failed to connect to %s:%u\n", host.c_str(), port);
    return false;
  }

  return true;
}

bool WebSocketsClient::Update() {
  if (_messages.size() > 0) {
    libwebsocket_callback_on_writable(_context, _wsi);
  }
  return libwebsocket_service(_context, 0) >= 0;
}

bool WebSocketsClient::Send(const char *buffer, size_t length) {
  Message *message = new Message;

  message->buffer = buffer;
  message->length = length;

  _messages.push(message);
  return true;
}

bool WebSocketsClient::Disconnect() {
  return true;
}

}  // namespace peeracle
