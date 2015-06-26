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

#include <cstring>
#include <string>
#include <sstream>
#include "third_party/libwebsockets/lib/libwebsockets.h"
#include "peeracle/Tracker/Client/TrackerClient.h"

#define MAX_TRACKER_PAYLOAD 32768

namespace peeracle {

struct TrackerClientUserdata {
  TrackerClient *client;
  unsigned char buffer[LWS_SEND_BUFFER_PRE_PADDING +
                       MAX_TRACKER_PAYLOAD + LWS_SEND_BUFFER_POST_PADDING];
};

static int TrackerClientCallback(struct libwebsocket_context *context,
                                 struct libwebsocket *wsi,
                                 enum libwebsocket_callback_reasons reason,
                                 void *user, void *in, size_t len) {
  switch (reason) {
    case LWS_CALLBACK_CLOSED:
      break;

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
      lwsl_info("got LWS_CALLBACK_CLIENT_CONNECTION_ERROR\n");
      return -1;

    case LWS_CALLBACK_CLIENT_ESTABLISHED:
      lwsl_notice("Client has connected\n");
      break;

    case LWS_CALLBACK_CLIENT_RECEIVE:
      lwsl_notice("Client RX: %s", reinterpret_cast<char *>(in));
      break;

    case LWS_CALLBACK_CLIENT_WRITEABLE:
      /* we will send our packet... */
      /*pss->len = sprintf((char *) &pss->buf[LWS_SEND_BUFFER_PRE_PADDING],
                         "hello from libwebsockets-test-echo client pid %d index %d\n",
                         getpid(), pss->index++);
      lwsl_notice("Client TX: %s", &pss->buf[LWS_SEND_BUFFER_PRE_PADDING]);
      n = libwebsocket_write(wsi, &pss->buf[LWS_SEND_BUFFER_PRE_PADDING],
                             pss->len, LWS_WRITE_TEXT);
      if (n < 0) {
        lwsl_err("ERROR %d writing to socket, hanging up\n", n);
        return -1;
      }
      if (n < (int) pss->len) {
        lwsl_err("Partial write\n");
        return -1;
      }*/
      break;
    case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
      break;
    default:
      break;
  }

  return 0;
}

static struct libwebsocket_protocols protocols[] = {
  {
    "default",
    TrackerClientCallback,
    sizeof(struct TrackerClientUserdata)
  },
  {
    NULL,
    NULL,
    0
  }
};

TrackerClient::TrackerClient() : _context(NULL), _wsi(NULL) {
#ifdef _DEBUG
  lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG |
                    LLL_HEADER, NULL);
#endif
}

TrackerClient::~TrackerClient() {
  if (_context) {
    libwebsocket_context_destroy(_context);
  }
}

bool TrackerClient::Init() {
  struct lws_context_creation_info info;

  memset(&info, 0, sizeof info);

  info.port = CONTEXT_PORT_NO_LISTEN;
  // info.iface = interface;
  info.protocols = protocols;
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

bool TrackerClient::Connect(const std::string &address, uint16_t port) {
  char uri[256] = "/";
  int use_ssl = 0;
  std::stringstream ads_port;

  if (!_context) {
    return false;
  }

  ads_port << address << ":" << port;

  _wsi = libwebsocket_client_connect_extended(_context, address.c_str(),
                                              port, use_ssl, uri,
                                              ads_port.str().c_str(),
                                              ads_port.str().c_str(), NULL, -1,
                                              this);

  if (!_wsi) {
    lwsl_err("Client failed to connect to %s:%u\n", address.c_str(), port);
    return false;
  }

  return true;
}

bool TrackerClient::Update() {
  return libwebsocket_service(_context, 0) >= 0;
}

}  // namespace peeracle
