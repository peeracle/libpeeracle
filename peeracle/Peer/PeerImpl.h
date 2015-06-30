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

#ifndef PEERACLE_PEER_PEERIMPL_H_
#define PEERACLE_PEER_PEERIMPL_H_

#include <string>
#include "third_party/webrtc/talk/app/webrtc/test/fakeconstraints.h"
#include "third_party/webrtc/talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/Peer/PeerInterface.h"

namespace peeracle {

class Peer::PeerImpl :
    public webrtc::PeerConnectionObserver {
 public:
  class CreateSDPObserver :
    public webrtc::CreateSessionDescriptionObserver {
   public:
    CreateSDPObserver(webrtc::PeerConnectionInterface *,
                      PeerInterface::CreateSDPObserver *);
    void OnSuccess(webrtc::SessionDescriptionInterface *desc);
    void OnFailure(const std::string& error);

   private:
    webrtc::PeerConnectionInterface *_peerConnection;
    PeerInterface::CreateSDPObserver *_createSDPObserver;
  };

  class SetLocalSDPObserver :
    public webrtc::SetSessionDescriptionObserver {
   public:
    SetLocalSDPObserver(webrtc::SessionDescriptionInterface *,
                        PeerInterface::CreateSDPObserver *);
    void OnSuccess();
    void OnFailure(const std::string& error);

   private:
    webrtc::SessionDescriptionInterface *_desc;
    PeerInterface::CreateSDPObserver *_createSDPObserver;
  };

  class SetRemoteSDPAndCreateAnswerObserver :
    public webrtc::SetSessionDescriptionObserver {
   public:
    SetRemoteSDPAndCreateAnswerObserver(
      webrtc::PeerConnectionInterface *peerConnection,
      webrtc::MediaConstraintsInterface *mediaConstraints,
      PeerInterface::CreateSDPObserver *);
    void OnSuccess();
    void OnFailure(const std::string& error);

   private:
    webrtc::PeerConnectionInterface *_peerConnection;
    webrtc::MediaConstraintsInterface *_mediaConstraints;
    PeerInterface::CreateSDPObserver *_createSDPObserver;
  };

  class SetRemoteSDPObserver :
    public webrtc::SetSessionDescriptionObserver {
   public:
    explicit SetRemoteSDPObserver(PeerInterface::SetSDPObserver *);
    void OnSuccess();
    void OnFailure(const std::string& error);

   private:
    PeerInterface::SetSDPObserver *_setSDPObserver;
  };

  class DataChannelObserver :
    public webrtc::DataChannelObserver {
   public:
    explicit DataChannelObserver(webrtc::DataChannelInterface *);
    void OnStateChange();
    void OnMessage(const webrtc::DataBuffer& buffer);

   private:
    webrtc::DataChannelInterface *_dataChannel;
  };

  explicit PeerImpl(PeerInterface::Observer *observer);
  virtual ~PeerImpl();

  void OnSignalingChange(
    webrtc::PeerConnectionInterface::SignalingState new_state);
  void OnStateChange(webrtc::PeerConnectionObserver::StateType state_changed);
  void OnAddStream(webrtc::MediaStreamInterface* stream);
  void OnRemoveStream(webrtc::MediaStreamInterface* stream);
  void OnDataChannel(webrtc::DataChannelInterface* data_channel);
  void OnRenegotiationNeeded();
  void OnIceConnectionChange(
    webrtc::PeerConnectionInterface::IceConnectionState new_state);
  void OnIceGatheringChange(
    webrtc::PeerConnectionInterface::IceGatheringState new_state);
  void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
  void OnIceComplete();

  PeerInterface::Observer *_observer;
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peerConnection;
  webrtc::FakeConstraints _mediaConstraints;
  rtc::scoped_refptr<webrtc::DataChannelInterface> _dataChannel;
  DataChannelObserver *_dataChannelObserver;
};

}  // namespace peeracle

#endif  // PEERACLE_PEER_PEERIMPL_H_
