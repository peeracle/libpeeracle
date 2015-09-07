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

#include <string>
#include <iostream>

#include "third_party/webrtc/webrtc/p2p/base/candidate.h"
#include "third_party/webrtc/webrtc/base/thread.h"
#include "third_party/webrtc/talk/app/webrtc/test/fakeconstraints.h"
#include "third_party/webrtc/talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/Peer/Peer.h"
#include "peeracle/Peer/PeerImpl.h"

namespace peeracle {

Peer::PeerImpl::PeerImpl(PeerInterface::PeerConnectionObserver *observer) :
  _observer(observer) {
  this->_mediaConstraints.AddOptional(
    webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
    webrtc::MediaConstraintsInterface::kValueTrue);
  this->_mediaConstraints.AddMandatory(
    webrtc::MediaConstraintsInterface::kOfferToReceiveAudio,
    webrtc::MediaConstraintsInterface::kValueFalse);
  this->_mediaConstraints.AddMandatory(
    webrtc::MediaConstraintsInterface::kOfferToReceiveVideo,
    webrtc::MediaConstraintsInterface::kValueFalse);
}

Peer::PeerImpl::~PeerImpl() {
}

Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver::
SetRemoteSDPAndCreateAnswerObserver(
  webrtc::PeerConnectionInterface *peerConnection,
  webrtc::MediaConstraintsInterface *mediaConstraints,
  PeerInterface::CreateSDPObserver *createSDPObserver) :
  _peerConnection(peerConnection),
  _mediaConstraints(mediaConstraints),
  _createSDPObserver(createSDPObserver) {
}

void Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver::OnSuccess() {
  rtc::scoped_refptr<Peer::PeerImpl::CreateSDPObserver>
    createOfferObserver =
    new rtc::RefCountedObject<Peer::PeerImpl::CreateSDPObserver>
      (_peerConnection, _createSDPObserver);

  _peerConnection->CreateAnswer(createOfferObserver, _mediaConstraints);
}

void Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver::OnFailure(
  const std::string &error) {
  _createSDPObserver->onCreateSDPFailure(error);
}

void Peer::PeerImpl::OnSignalingChange(
  webrtc::PeerConnectionInterface::SignalingState new_state) {
  _observer->onSignalingChange(new_state);
}

void Peer::PeerImpl::OnStateChange(
  webrtc::PeerConnectionObserver::StateType state_changed) {
  _observer->onStateChange(state_changed);
}

void Peer::PeerImpl::OnAddStream(webrtc::MediaStreamInterface* stream) {
}

void Peer::PeerImpl::OnRemoveStream(webrtc::MediaStreamInterface* stream) {
}

void Peer::PeerImpl::OnDataChannel(webrtc::DataChannelInterface* data_channel) {
  _dataChannel = data_channel;
  _dataChannelObserver = new PeerImpl::DataChannelObserver(_observer,
                                                           data_channel);
  _dataChannel->RegisterObserver(_dataChannelObserver);
  std::cout << "PeerImpl::OnDataChannel " << _dataChannel->state() << std::endl;
}

void Peer::PeerImpl::OnRenegotiationNeeded() {
}

void Peer::PeerImpl::OnIceConnectionChange(
  webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  _observer->onIceConnectionChange(new_state);
}

void Peer::PeerImpl::OnIceGatheringChange(
  webrtc::PeerConnectionInterface::IceGatheringState new_state) {
  _observer->onIceGatheringChange(new_state);
}

void Peer::PeerImpl::OnIceCandidate(
  const webrtc::IceCandidateInterface* candidate) {
  std::string sdp;
  if (!candidate->ToString(&sdp)) {
    LOG(LS_ERROR) << "Failed to serialize candidate";
    return;
  }

  _observer->onIceCandidate(candidate->sdp_mid(), candidate->sdp_mline_index(),
                            sdp);
}

void Peer::PeerImpl::OnIceComplete() {
}

}  // namespace peeracle
