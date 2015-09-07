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
    TrackerMessageInterface *msg =
      new TrackerMessage(TrackerMessageInterface::kHello);
    _client->send(msg);
  }

  void onMessage(const char *buffer, size_t length) {
    int type;
    DataStreamInit dsInit;
    dsInit.bigEndian = true;
    MemoryDataStream *dataStream = new MemoryDataStream(dsInit);
    TrackerMessageInterface *message = new TrackerMessage();

    dataStream->write(buffer, length);
    dataStream->seek(0);
    if (!message->unserialize(dataStream)) {
      delete dataStream;
      return;
    }
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
      case TrackerMessageInterface::kEnter:
      case TrackerMessageInterface::kPoke:
      {
        std::string hash;
        std::string peer;
        std::vector<uint32_t> got;
        uint32_t value;
        uint32_t gotCount;
        std::stringstream strm;

        message->get("hash", &hash, "");
        message->get("peer", &peer, "");
        message->get("got", &gotCount, 0);

        for (uint32_t i = 0; i < gotCount; ++i) {
          strm.clear();
          strm.str("");
          strm << "got" << i;
          message->get(strm.str(), &value, 0);
          got.push_back(value);
        }

        _observer->onEnter(hash, peer, got);
        break;
      }
      case TrackerMessageInterface::kSdp:
      {
        std::string id;
        std::string hash;
        std::string stype;

        message->get("id", &id, "");
        message->get("hash", &hash, "");
        message->get("type", &stype, "");

        if (stype == "offer" || stype == "answer") {
          std::string sdp;

          message->get("sdp", &sdp, "");

          _observer->onSdp(id, hash, stype, sdp);
        } else if (stype == "ice") {
          std::string candidate;
          std::string sdpMid;
          uint32_t sdpMLineIndex;

          message->get("candidate", &candidate, "");
          message->get("sdpMid", &sdpMid, "");
          message->get("sdpMLineIndex", &sdpMLineIndex, 0);

          _observer->onIceCandidate(id, hash, candidate, sdpMid, sdpMLineIndex);
        }
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

void TrackerClient::announce(const std::string &id,
                             const std::vector<uint32_t> &got) {
  std::stringstream strm;
  TrackerMessageInterface *msg = new TrackerMessage(
    TrackerMessageInterface::kAnnounce);

  msg->set("hash", id);
  msg->set("got", static_cast<uint32_t>(got.size()));

  for (uint32_t i = 0; i < got.size(); ++i) {
    strm.clear();
    strm.str("");
    strm << "got" << i;
    msg->set(strm.str(), got[i]);
  }

  this->send(msg);
  delete msg;
}

void TrackerClient::sendSdp(const std::string &id, const std::string &hash,
                            const std::string &sdp, const std::string &type) {
  TrackerMessageInterface *msg = new TrackerMessage(
    TrackerMessageInterface::kSdp);

  msg->set("id", id);
  msg->set("hash", hash);
  msg->set("type", type);
  msg->set("sdp", sdp);

  this->send(msg);
  delete msg;
}


void TrackerClient::sendIceCandidate(const std::string &id,
                                     const std::string &hash,
                                     const std::string &sdpMid,
                                     uint32_t sdpMLineIndex,
                                     const std::string &candidate) {
  TrackerMessageInterface *msg = new TrackerMessage(
    TrackerMessageInterface::kSdp);

  msg->set("id", id);
  msg->set("hash", hash);
  msg->set("type", "ice");
  msg->set("sdpMid", sdpMid);
  msg->set("sdpMLineIndex", sdpMLineIndex);
  msg->set("candidate", candidate);

  this->send(msg);
  delete msg;
}

void TrackerClient::send(TrackerMessageInterface *message) {
  char *buffer;
  DataStreamInit dsInit;
  dsInit.bigEndian = true;
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
