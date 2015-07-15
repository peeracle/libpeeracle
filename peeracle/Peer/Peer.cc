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
#include "peeracle/peeracle.h"

namespace peeracle {

Peer::Peer(PeerInterface::Observer *observer) :
  _peer(new Peer::PeerImpl(observer)) {
  webrtc::PeerConnectionInterface::IceServers iceServers;
  webrtc::PeerConnectionInterface::IceServer amazonIceServer;
  webrtc::PeerConnectionInterface::IceServer googleIceServer;
  webrtc::PeerConnectionInterface::IceServer ekigaIceServer;
  webrtc::PeerConnectionInterface::IceServer ideasipIceServer;
  webrtc::PeerConnectionInterface::IceServer rixtelecomIceServer;
  webrtc::PeerConnectionInterface::IceServer schlundIceServer;
  webrtc::PeerConnectionInterface::IceServer stunprotocolIceServer;
  webrtc::PeerConnectionInterface::IceServer voiparoundIceServer;
  webrtc::PeerConnectionInterface::IceServer voipbusterIceServer;
  webrtc::PeerConnectionInterface::IceServer voipstuntIceServer;
  webrtc::PeerConnectionInterface::IceServer voipgratiaIceServer;

  amazonIceServer.uri = "stun:23.21.150.121";
  googleIceServer.uri = "stun:stun.l.google.com:19302";
  ekigaIceServer.uri = "stun:stun.ekiga.net";
  ideasipIceServer.uri = "stun:stun.ideasip.com";
  rixtelecomIceServer.uri = "stun:stun.rixtelecom.se";
  schlundIceServer.uri = "stun:stun.schlund.de";
  stunprotocolIceServer.uri = "stun:stun.stunprotocol.org:3478";
  voiparoundIceServer.uri = "stun:stun.voiparound.com";
  voipbusterIceServer.uri = "stun:stun.voipbuster.com";
  voipstuntIceServer.uri = "stun:stun.voipstunt.com";
  voipgratiaIceServer.uri = "stun:stun.voxgratia.org";

  amazonIceServer.urls.push_back("stun:23.21.150.121");
  googleIceServer.urls.push_back("stun:stun.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun1.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun2.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun3.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun4.l.google.com:19302");
  ekigaIceServer.urls.push_back("stun:stun.ekiga.net");
  ideasipIceServer.urls.push_back("stun:stun.ideasip.com");
  rixtelecomIceServer.urls.push_back("stun:stun.rixtelecom.se");
  schlundIceServer.urls.push_back("stun:stun.schlund.de");
  stunprotocolIceServer.urls.push_back("stun:stun.stunprotocol.org:3478");
  voiparoundIceServer.urls.push_back("stun:stun.voiparound.com");
  voipbusterIceServer.urls.push_back("stun:stun.voipbuster.com");
  voipstuntIceServer.urls.push_back("stun:stun.voipstunt.com");
  voipgratiaIceServer.urls.push_back("stun:stun.voxgratia.org");

  iceServers.push_back(amazonIceServer);
  iceServers.push_back(googleIceServer);
  iceServers.push_back(ekigaIceServer);
  iceServers.push_back(ideasipIceServer);
  iceServers.push_back(rixtelecomIceServer);
  iceServers.push_back(schlundIceServer);
  iceServers.push_back(stunprotocolIceServer);
  iceServers.push_back(voiparoundIceServer);
  iceServers.push_back(voipbusterIceServer);
  iceServers.push_back(voipstuntIceServer);
  iceServers.push_back(voipgratiaIceServer);

  /*_peer->_peerConnection = peeracle::getPeerConnectionFactory()->
    CreatePeerConnection(iceServers, &this->_peer->_mediaConstraints,
                         NULL, NULL, _peer);*/
}

Peer::~Peer() {
  _peer->_peerConnection = NULL;
  _peer->_dataChannel = NULL;
  if (_peer->_dataChannelObserver) {
    delete _peer->_dataChannelObserver;
  }
  delete _peer;
}

void Peer::CreateOffer(PeerInterface::CreateSDPObserver
                       *createSDPObserver) {
  webrtc::DataChannelInit init;
  rtc::scoped_refptr<Peer::PeerImpl::CreateSDPObserver>
    createOfferObserver =
    new rtc::RefCountedObject<Peer::PeerImpl::CreateSDPObserver>
      (_peer->_peerConnection, createSDPObserver);

  init.reliable = true;
  _peer->_dataChannel =
    _peer->_peerConnection->CreateDataChannel("signal", &init);
  _peer->_dataChannelObserver = new PeerImpl::DataChannelObserver
    (_peer->_dataChannel);
  _peer->_dataChannel->RegisterObserver(_peer->_dataChannelObserver);

  _peer->_peerConnection->CreateOffer(createOfferObserver,
                                      &_peer->_mediaConstraints);
}

void Peer::CreateAnswer(const std::string &sdp,
                        PeerInterface::CreateSDPObserver *createSDPObserver) {
  webrtc::SessionDescriptionInterface *desc;
  rtc::scoped_refptr<Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver>
    setOfferObserver =
    new rtc::RefCountedObject
      <Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver>
      (_peer->_peerConnection, &_peer->_mediaConstraints, createSDPObserver);

  desc = webrtc::CreateSessionDescription("offer", sdp);
  if (!desc) {
    return;
  }

  _peer->_peerConnection->SetRemoteDescription(setOfferObserver, desc);
}

void Peer::SetAnswer(const std::string &sdp,
                     PeerInterface::SetSDPObserver *setSDPObserver) {
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("answer", sdp);

  if (!desc) {
    return;
  }

  rtc::scoped_refptr<Peer::PeerImpl::SetRemoteSDPObserver>
    setAnswerObserver =
    new rtc::RefCountedObject<Peer::PeerImpl::SetRemoteSDPObserver>
      (setSDPObserver);

  _peer->_peerConnection->SetRemoteDescription(setAnswerObserver, desc);
}

void Peer::AddICECandidate(const std::string &sdpMid,
                           int sdpMLineIndex,
                           const std::string &candidate) {
  rtc::scoped_ptr<webrtc::IceCandidateInterface> iceCandidate(
    webrtc::CreateIceCandidate(sdpMid, sdpMLineIndex, candidate,
                               NULL));

  if (!iceCandidate) {
    return;
  }

  _peer->_peerConnection->AddIceCandidate(iceCandidate.get());
}

}  // namespace peeracle
