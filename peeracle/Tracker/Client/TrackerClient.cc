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
#include <string>
#include <iostream>

#include "peeracle/DataStream/MemoryDataStream.h"
#include "peeracle/Tracker/Client/TrackerClient.h"
#include "peeracle/Tracker/Message/TrackerMessage.h"
#include "peeracle/WebSocketsClient/WebSocketsClient.h"

namespace peeracle {

class TrackerWebSocketsClientObserver : public WebSocketsClientObserver {
 public:
  explicit TrackerWebSocketsClientObserver(TrackerClient *client,
                                           TrackerClientObserver *observer) :
    _client(client), _observer(observer) {
  }

  void onConnect() {
    TrackerMessageInterface *msg = new TrackerMessage(
      TrackerMessageInterface::kHello);

    _client->_send(msg);
    delete msg;
  }

  void onMessage(const char *buffer, size_t length) {
    int type;
    DataStreamInit dsInit;
    MemoryDataStream *dataStream = new MemoryDataStream(dsInit);
    TrackerMessageInterface *message = new TrackerMessage();

    dataStream->write(buffer, length);
    dataStream->seek(0);
    message->unserialize(dataStream);
    delete dataStream;

    type = message->getType();
    std::cout << "Got message type " << static_cast<int>(type) << std::endl;
    switch (type) {
      case TrackerMessageInterface::kWelcome:
      {
        std::string id;

        message->get("id", &id, "");

        _observer->onConnect(id);
        break;
      }
      case TrackerMessageInterface::kPoke:
      {
        std::string hash;
        std::string peer;
        uint32_t got;

        message->get("hash", &hash, "");
        message->get("peer", &peer, "");
        message->get("got", &got, 0);

        _observer->onPeerConnect(hash, peer, got, true);
        break;
      }
      default:
        break;
    }

    delete message;
  }

  void onDisconnect() {
    _observer->onDisconnect();
  }

  void onError() {
  }

 protected:
  TrackerClient *_client;
  TrackerClientObserver *_observer;
};

TrackerClient::TrackerClient(const std::string &url,
                             TrackerClientObserver *observer) :
  _url(url), _observer(observer) {
  _webSocketsClientObserver = new TrackerWebSocketsClientObserver(this,
                                                                  observer);
  _webSocketsClient = new WebSocketsClient(url, _webSocketsClientObserver);
}

TrackerClient::~TrackerClient() {
  delete _webSocketsClient;
}

bool TrackerClient::Init() {
  return _webSocketsClient->Init();
}

bool TrackerClient::Connect() {
  return _webSocketsClient->Connect();
}

bool TrackerClient::Update() {
  return _webSocketsClient->Update();
}

const std::string &TrackerClient::getUrl() const {
  return _url;
}

void TrackerClient::announce(const std::string id, uint32_t got) {
  TrackerMessageInterface *msg = new TrackerMessage(
    TrackerMessageInterface::kAnnounce);

  msg->set("hash", id);
  msg->set("got", got);

  _send(msg);
  delete msg;
}

void TrackerClient::_send(TrackerMessageInterface *message) {
  char *buffer;
  DataStreamInit dsInit;
  MemoryDataStream *dataStream = new MemoryDataStream(dsInit);
  std::streamsize length;

  message->serialize(dataStream);
  dataStream->seek(0);

  length = dataStream->length();
  buffer = new char[length];

  dataStream->read(buffer, length);

  _webSocketsClient->Send(buffer, static_cast<size_t>(length));

  delete dataStream;
}

}  // namespace peeracle
