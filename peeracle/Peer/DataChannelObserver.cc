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

#include <iostream>

#include "peeracle/DataStream/MemoryDataStream.h"
#include "peeracle/Peer/Peer.h"
#include "peeracle/Peer/PeerImpl.h"
#include "peeracle/Peer/PeerMessage.h"

namespace peeracle {

Peer::PeerImpl::DataChannelObserver::DataChannelObserver(
  PeerInterface::PeerConnectionObserver *observer,
  webrtc::DataChannelInterface *dataChannel)
    : _observer(observer), _dataChannel(dataChannel) {
  (void)_observer;
}

void Peer::PeerImpl::DataChannelObserver::OnStateChange() {
  std::cout << "DataChannelObserver::OnStateChange " <<
  this->_dataChannel->state() << std::endl;

  if (this->_dataChannel->state() == webrtc::DataChannelInterface::kOpen) {
    uint8_t data[] = {0};
    rtc::Buffer buffer(data, sizeof(data));
    webrtc::DataBuffer dataBuffer(buffer, true);

    this->_dataChannel->Send(dataBuffer);
  }
}

void Peer::PeerImpl::DataChannelObserver::OnMessage(
  const webrtc::DataBuffer& buffer) {
  DataStreamInit init;
  init.bigEndian = true;
  MemoryDataStream *dataStream = new MemoryDataStream(init);
  PeerMessageInterface *message = new PeerMessage();

  dataStream->write(reinterpret_cast<const char*>(buffer.data.data()),
               buffer.size());
  dataStream->seek(0);

  if (!message->unserialize(dataStream)) {
    delete message;
    delete dataStream;
    return;
  }

  _observer->onMessage(message, dataStream);
  delete message;
  delete dataStream;
}

}  // namespace peeracle
