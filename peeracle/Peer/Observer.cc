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

void Peer::PeerImpl::OnSignalingChange(
  webrtc::PeerConnectionInterface::SignalingState new_state) {
  this->_observer->onSignalingChange(new_state);
}

void Peer::PeerImpl::OnStateChange(webrtc::PeerConnectionObserver::StateType
                                   state_changed) {
  this->_observer->onStateChange(state_changed);
}

void Peer::PeerImpl::OnAddStream(webrtc::MediaStreamInterface *stream) {
}

void Peer::PeerImpl::OnRemoveStream(webrtc::MediaStreamInterface *stream) {
}

void Peer::PeerImpl::OnDataChannel(webrtc::DataChannelInterface *data_channel) {
  std::cout << "Peer::PeerImpl::OnDataChannel " << data_channel->label() <<
  std::endl;
  this->_dataChannel = data_channel;
  this->_dataChannelObserver = new PeerImpl::DataChannelObserver(data_channel);
  this->_dataChannel->RegisterObserver(this->_dataChannelObserver);
}

void Peer::PeerImpl::OnRenegotiationNeeded() {
}

void Peer::PeerImpl::OnIceConnectionChange(
  webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  this->_observer->onIceConnectionChange(new_state);
}

void Peer::PeerImpl::OnIceGatheringChange(
  webrtc::PeerConnectionInterface::IceGatheringState new_state) {
  this->_observer->onIceGatheringChange(new_state);
}

void Peer::PeerImpl::OnIceCandidate(
  const webrtc::IceCandidateInterface *candidate) {
  std::string sdpMid = candidate->sdp_mid();
  int sdpMLineIndex = candidate->sdp_mline_index();
  std::string cand;

  candidate->ToString(&cand);
  this->_observer->onIceCandidate(sdpMid, sdpMLineIndex, cand);
}

void Peer::PeerImpl::OnIceComplete() {
}

}  // namespace peeracle
