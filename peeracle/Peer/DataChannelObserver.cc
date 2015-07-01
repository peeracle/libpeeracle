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
#include "peeracle/Peer/Peer.h"
#include "peeracle/Peer/PeerImpl.h"

namespace peeracle {

Peer::PeerImpl::DataChannelObserver::DataChannelObserver(
  webrtc::DataChannelInterface *dataChannel) : _dataChannel(dataChannel) {
}

void Peer::PeerImpl::DataChannelObserver::OnStateChange() {
  std::cout << "DataChannelObserver::OnStateChange " <<
  this->_dataChannel->state() << std::endl;

  if (this->_dataChannel->state() == webrtc::DataChannelInterface::kOpen) {
    uint8_t data[] = {0, 16, 32, 64};
    rtc::Buffer buffer(data, sizeof(data));
    webrtc::DataBuffer dataBuffer(buffer, true);

    std::cout << "SEND MSG NOW" << std::endl;
    this->_dataChannel->Send(dataBuffer);
  }
}

void Peer::PeerImpl::DataChannelObserver::OnMessage(
  const webrtc::DataBuffer& buffer) {
  std::cout << "GOT MSG!!!" << std::endl;
  std::cout << "size = " << buffer.size() << std::endl;
  for (size_t i = 0; i < buffer.size(); ++i) {
    printf("data[%zu] = %d\n", i, buffer.data.data()[i]);
  }
}

}  // namespace peeracle
