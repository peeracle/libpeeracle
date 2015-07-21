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

#include "peeracle/Tracker/Client/TrackerClient.h"
#include "peeracle/Tracker/Client/TrackerClientImpl.h"
#include "peeracle/Tracker/Message/TrackerMessage.h"

namespace peeracle {

TrackerClient::TrackerClient(const std::string &url,
                             TrackerClientObserver *observer) :
  _url(url), _impl(new TrackerClientImpl(url, observer)) {
}

TrackerClient::~TrackerClient() {
  delete _impl;
}

bool TrackerClient::Init() {
  return _impl->Init();
}

bool TrackerClient::Connect() {
  return _impl->Connect();
}

bool TrackerClient::Update() {
  return _impl->Update();
}

const std::string &TrackerClient::getUrl() const {
  return _url;
}

void TrackerClient::announce(const std::string id, uint32_t got) {
  TrackerMessageInterface *msg = new TrackerMessage(
    TrackerMessageInterface::kAnnounce);

  msg->set("hash", id);
  msg->set("got", got);

  _impl->Send(msg);
}

}  // namespace peeracle
