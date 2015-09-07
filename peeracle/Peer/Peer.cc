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

#include "peeracle/DataStream/MemoryDataStream.h"
#include "peeracle/Peer/Peer.h"
#include "peeracle/Peer/PeerImpl.h"
#include "peeracle/Peer/PeerMessage.h"
#include "peeracle/peeracle.h"

namespace peeracle {

Peer::Peer(PeerInterface::Observer *observer, const std::string &id,
           TrackerClientInterface *tracker) :
  _peer(new Peer::PeerImpl(this)),
  _observer(observer),
  _id(id),
  _tracker(tracker),
  _request(NULL),
  _state(State::Disconnected) {
  webrtc::PeerConnectionInterface::IceServers iceServers;
  webrtc::PeerConnectionInterface::IceServer googleIceServer;

  googleIceServer.uri = "stun:stun.l.google.com:19302";
  googleIceServer.urls.push_back("stun:stun.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun1.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun2.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun3.l.google.com:19302");
  googleIceServer.urls.push_back("stun:stun4.l.google.com:19302");

  iceServers.push_back(googleIceServer);

  _peer->_peerConnection = peeracle::getPeerConnectionFactory()->
    CreatePeerConnection(iceServers, &this->_peer->_mediaConstraints,
                         NULL, NULL, _peer);
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
    _peer->_peerConnection->CreateDataChannel("prcl", &init);
  _peer->_dataChannelObserver = new PeerImpl::DataChannelObserver
    (this, _peer->_dataChannel);
  _peer->_dataChannel->RegisterObserver(_peer->_dataChannelObserver);

  _peer->_peerConnection->CreateOffer(createOfferObserver,
                                      &_peer->_mediaConstraints);
}

void Peer::CreateAnswer(const std::string &sdp,
                        PeerInterface::CreateSDPObserver *createSDPObserver) {
  webrtc::SdpParseError error;
  webrtc::SessionDescriptionInterface *desc;
  rtc::scoped_refptr<Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver>
    setOfferObserver =
    new rtc::RefCountedObject
      <Peer::PeerImpl::SetRemoteSDPAndCreateAnswerObserver>
      (_peer->_peerConnection, &_peer->_mediaConstraints, createSDPObserver);

  desc = webrtc::CreateSessionDescription("offer", sdp, &error);
  if (!desc) {
    LOG(WARNING) << "Can't parse received session description message. "
                 << "SdpParseError was: " << error.description;
    return;
  }

  _peer->_peerConnection->SetRemoteDescription(setOfferObserver, desc);
}

void Peer::SetAnswer(const std::string &sdp,
                     PeerInterface::SetSDPObserver *setSDPObserver) {
  webrtc::SdpParseError error;
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("answer", sdp, &error);

  if (!desc) {
    LOG(WARNING) << "Can't parse received session description message. "
                 << "SdpParseError was: " << error.description;
    return;
  }

  rtc::scoped_refptr<Peer::PeerImpl::SetRemoteSDPObserver>
    setAnswerObserver =
    new rtc::RefCountedObject<Peer::PeerImpl::SetRemoteSDPObserver>
      (setSDPObserver);

  _peer->_peerConnection->SetRemoteDescription(setAnswerObserver, desc);
}

void Peer::AddICECandidate(const std::string &sdpMid, int sdpMLineIndex,
                           const std::string &candidate) {
  webrtc::SdpParseError error;
  rtc::scoped_ptr<webrtc::IceCandidateInterface> iceCandidate(
    webrtc::CreateIceCandidate(sdpMid, sdpMLineIndex, candidate,
                               &error));

  if (!iceCandidate) {
    LOG(WARNING) << "Can't parse received session description message. "
                 << "SdpParseError was: " << error.description;
    return;
  }

  _peer->_peerConnection->AddIceCandidate(iceCandidate.get());
}

void Peer::onCreateSDPSuccess(const std::string &sdp, const std::string &type) {
  if (!_request) {
    return;
  }

  _state = State::Connecting;
  _tracker->sendSdp(_id, _request->hash, sdp, type);
}

void Peer::onCreateSDPFailure(const std::string &error) {
  _state = State::Disconnected;
}

void Peer::onSetSDPSuccess() {
  _state = State::Connecting;
}

void Peer::onSetSDPFailure(const std::string &error) {
  _state = State::Disconnected;
}

void Peer::onIceCandidate(const std::string &sdpMid, int sdpMLineIndex,
                          const std::string &candidate) {
  _tracker->sendIceCandidate(_id, _request->hash, sdpMid,
                             static_cast<uint32_t>(sdpMLineIndex), candidate);
}

void Peer::onSignalingChange(int state) {
}

void Peer::onStateChange(int state) {
}

void Peer::onIceConnectionChange(int state) {
}

void Peer::onIceGatheringChange(int state) {
}

void Peer::onMessage(PeerMessageInterface *message, DataStream *dataStream) {
  std::cout << "got message" << std::endl;

  int type = message->getType();

  switch (type) {
    case PeerMessageInterface::kPing:
    {
      if (_state == State::Connecting) {
        _state = State::Connected;
        std::cout << "PING RECEIVED" << std::endl;
        _observer->onConnect();
      }
      break;
    }
    case PeerMessageInterface::kChunk:
    {
      std::string hash;
      uint32_t segment;
      uint32_t chunk;
      uint32_t offset;
      uint32_t length;

      message->get("hash", &hash, "");
      message->get("segment", &segment, 0);
      message->get("chunk", &chunk, 0);
      message->get("offset", &offset, 0);
      message->get("length", &length, 0);

      char *bytes = new char[length];
      dataStream->read(bytes, length);

      _observer->onChunk(hash, segment, chunk, offset, length, bytes);
      delete[] bytes;
      break;
    }
    default:
      break;
  }
}

void Peer::addHash(const std::string &hash, const std::vector<uint32_t> &got) {
  _hashes[hash] = got;
}

const std::map<std::string, std::vector<uint32_t>> &Peer::getHashes() const {
  return _hashes;
}

const std::string &Peer::getId() const {
  return _id;
}

SessionHandleInterface::Request *Peer::getRequest() const {
  return _request;
}

void Peer::sendRequest(SessionHandleInterface::Request *request) {
  std::cout << "[Peer::sendRequest]" << std::endl;
  _request = request;

  if (_state == State::Disconnected) {
    CreateOffer(this);
    return;
  }

  std::cout << "[Peer::sendRequest] Send the request NOW " << request->hash <<
  " " << request->segment << " " << request->chunk << std::endl;

  PeerMessageInterface *message =
    new PeerMessage(PeerMessageInterface::kRequest);

  message->set("hash", request->hash);
  message->set("segment", request->segment);
  message->set("chunk", request->chunk);

  _sendMessage(message);
}

void Peer::_sendMessage(PeerMessageInterface *message) {
  char *bytes;
  DataStreamInit dsInit;
  dsInit.bigEndian = true;
  MemoryDataStream *dataStream = new MemoryDataStream(dsInit);
  std::streamsize length;

  message->serialize(dataStream);
  dataStream->seek(0);

  length = dataStream->length();
  bytes = new char[length];

  std::cout << "send " << length << " bytes" << std::endl;
  dataStream->read(bytes, length);
  rtc::Buffer buffer(bytes, length);
  webrtc::DataBuffer dataBuffer(buffer, true);
  _peer->_dataChannel->Send(dataBuffer);

  delete dataStream;
  delete bytes;
}

void Peer::processSdp(const std::string &type, const std::string &sdp) {
  std::cout << "[Peer::processSdp] " << type << std::endl;
  if (type == "offer") {
    CreateAnswer(sdp, this);
  } else if (type == "answer") {
    SetAnswer(sdp, this);
  }
}

void Peer::processIceCandidate(const std::string &candidate,
                               const std::string &sdpMid,
                               uint32_t sdpMLineIndex) {
  AddICECandidate(sdpMid, sdpMLineIndex, candidate);
  std::cout << "[Peer::processIceCandidate]" << std::endl;
}

}  // namespace peeracle
