#include <iostream>
#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/scoped_ref_ptr.h"
#include "webrtc/base/thread.h"
#include "createofferobserver.h"
#include "setremoteofferobserver.h"
#include "setsessiondescriptionobserver.h"
#include "manager.h"
#include "peer.h"

namespace peeracle {

class Peer::PeerImpl : public webrtc::PeerConnectionObserver {
 public:
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peerConnection;

  rtc::Thread *_signaling_thread;
  rtc::Thread *_worker_thread;
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
    _peerConnectionFactory;

  std::list<PeerInterface::Observer*> _peerObservers;

 private:
  void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState state);
  void OnStateChange(StateType state_changed);
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
};

Peer::Peer() : peer_(new PeerImpl) {
  webrtc::PeerConnectionInterface::IceServers iceServers;
  webrtc::PeerConnectionInterface::IceServer iceServer;
  iceServer.uri = "stun:stun.l.google.com:19302";
  iceServers.push_back(iceServer);

  webrtc::FakeConstraints constr;
  constr.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
                     webrtc::MediaConstraintsInterface::kValueTrue);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveAudio,
                      webrtc::MediaConstraintsInterface::kValueFalse);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveVideo,
                      webrtc::MediaConstraintsInterface::kValueFalse);

  rtc::ThreadManager::Instance()->WrapCurrentThread();
  /*peer_->_worker_thread = new rtc::Thread();
  peer_->_worker_thread->SetName("worker_thread", NULL);
  peer_->_signaling_thread = new rtc::Thread();
  peer_->_signaling_thread->SetName("signaling_thread", NULL);
  CHECK(peer_->_worker_thread->Start() && peer_->_signaling_thread->Start())
  << "Failed to start threads";*/

  peer_->_signaling_thread = (rtc::Thread*)peeracle::Manager::getSingleton().
    getSignalingThread();
  peer_->_worker_thread = (rtc::Thread*)peeracle::Manager::getSingleton().
    getWorkerThread();

  peer_->_peerConnectionFactory = webrtc::CreatePeerConnectionFactory(
    peer_->_worker_thread, peer_->_signaling_thread, NULL, NULL, NULL);

  peer_->_peerConnection = peer_->_peerConnectionFactory->CreatePeerConnection(
    iceServers, &constr, NULL, NULL, peer_);
}

void Peer::subscribe(PeerInterface::Observer *observer) {
  peer_->_peerObservers.push_back(observer);
}

void Peer::unsubscribe(PeerInterface::Observer *observer) {
  std::remove(peer_->_peerObservers.begin(), peer_->_peerObservers.end(),
              observer);
}

void Peer::createOffer(PeerInterface::SessionDescriptionObserver *observer) {
  rtc::scoped_refptr<CreateOfferObserver>
    createOfferObserver =
    new rtc::RefCountedObject<CreateOfferObserver>
      (peer_->_peerConnection, observer);

  // webrtc::DataChannelInit dataChannelInit;
  // _dataChannel = _peerConnection->CreateDataChannel("signal",
  //  &dataChannelInit);

  peer_->_peerConnection->CreateOffer(createOfferObserver, NULL);
}

bool Peer::createAnswer(const std::string &sdp,
                        PeerInterface::SessionDescriptionObserver *observer) {
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("offer", sdp);

  if (!desc) {
    return false;
  }

  rtc::scoped_refptr<SetRemoteOfferObserver>
    setRemoteOfferObserver =
    new rtc::RefCountedObject<SetRemoteOfferObserver>
      (peer_->_peerConnection, observer);

  peer_->_peerConnection->SetRemoteDescription(setRemoteOfferObserver, desc);
  return true;
}

bool Peer::setAnswer(const std::string &sdp,
                     PeerInterface::SessionDescriptionObserver *observer) {
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("answer", sdp);

  if (!desc) {
    return false;
  }

  rtc::scoped_refptr<SetSessionDescriptionObserver>
    setAnswerObserver =
    new rtc::RefCountedObject<SetSessionDescriptionObserver>
      (observer);

  peer_->_peerConnection->SetRemoteDescription(setAnswerObserver, desc);
  return true;
}

bool Peer::addIceCandidate(const std::string &sdpMid,
                           int sdpMLineIndex,
                           const std::string &candidate) {
  rtc::scoped_ptr<webrtc::IceCandidateInterface> iceCandidate(
    webrtc::CreateIceCandidate(sdpMid, sdpMLineIndex, candidate));

  if (!iceCandidate) {
    return false;
  }

  peer_->_peerConnection->AddIceCandidate(iceCandidate.get());
  return true;
}

void Peer::PeerImpl::OnSignalingChange
  (webrtc::PeerConnectionInterface::SignalingState state) {
  for (std::list<PeerInterface::Observer *>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onSignalingChange(state);
  }
}

void Peer::PeerImpl::OnStateChange(StateType state_changed) {
  for (std::list<PeerInterface::Observer *>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onStateChange(state_changed);
  }
}

void Peer::PeerImpl::OnAddStream(webrtc::MediaStreamInterface *stream) {
  std::cout << "Peer::OnAddStream " << std::endl;
}

void Peer::PeerImpl::OnRemoveStream(webrtc::MediaStreamInterface *stream) {
  std::cout << "Peer::OnRemoveStream " << std::endl;
}

void Peer::PeerImpl::OnDataChannel(webrtc::DataChannelInterface *data_channel) {
  std::cout << "Peer::OnDataChannel " << data_channel->label() <<
  std::endl;
}

void Peer::PeerImpl::OnRenegotiationNeeded() {
  std::cout << "Peer::OnRenegotiationNeeded " << std::endl;
}

void Peer::PeerImpl::OnIceConnectionChange(
  webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  for (std::list<PeerInterface::Observer *>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceConnectionChange(new_state);
  }
}

void Peer::PeerImpl::OnIceGatheringChange(
  webrtc::PeerConnectionInterface::IceGatheringState new_state) {
  for (std::list<PeerInterface::Observer *>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceGatheringChange(new_state);
  }
}

void Peer::PeerImpl::OnIceCandidate(const webrtc::IceCandidateInterface *candidate) {
  std::string cand;

  candidate->ToString(&cand);
  for (std::list<PeerInterface::Observer *>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceCandidate(candidate->sdp_mid(), candidate->sdp_mline_index(),
                          cand);
  }
}

void Peer::PeerImpl::OnIceComplete() {
  std::cout << "Peer::OnIceComplete " <<
  std::endl;
}

}
