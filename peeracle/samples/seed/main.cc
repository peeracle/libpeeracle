#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>

#include "../../lib/peer.h"
#include "../../lib/manager.h"

#define PEERACLE_SAMPLE_HASH "abc"
#define PEERACLE_SAMPLE_GOT "000"

peeracle::Peer *peerA;
peeracle::Peer *peerB;

class MyPeerAObserver : public peeracle::PeerInterface::Observer {
 public:
  explicit MyPeerAObserver() {

  }

  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "PeerA ICE : " << peerA << " " << candidate << std::endl;
    peerB->addIceCandidate(sdpMid, sdpMLineIndex, candidate);
  }

  void onSignalingChange(int state) {
    std::cout << "PeerA onSignalingChange : " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "PeerA onStateChange : " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "PeerA onIceConnectionChange : " << state << std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "PeerA onIceGatheringChange : " << state << std::endl;
  }

 protected:
  ~MyPeerAObserver() {

  }
};

class MyPeerBObserver : public peeracle::PeerInterface::Observer {
 public:
  explicit MyPeerBObserver() {

  }

  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "PeerB ICE : " << peerB << " " << candidate << std::endl;
    peerA->addIceCandidate(sdpMid, sdpMLineIndex, candidate);
  }

  void onSignalingChange(int state) {
    std::cout << "PeerB onSignalingChange : " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "PeerB onStateChange : " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "PeerB onIceConnectionChange : " << state << std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "PeerB onIceGatheringChange : " << state << std::endl;
  }

 protected:
  ~MyPeerBObserver() {

  }
};

class MyPeerASessionDescriptionObserver
  : public peeracle::PeerInterface::SessionDescriptionObserver {
 public:
  explicit MyPeerASessionDescriptionObserver(peeracle::PeerInterface *peerA,
                                             peeracle::PeerInterface *peerB);

  void onCreateSuccess(const std::string &sdp, const std::string &type);
  void onSetSuccess();
  void onCreateFailure(const std::string &error);
  void onSetFailure(const std::string &error);

 protected:
  ~MyPeerASessionDescriptionObserver() {

  }

 private:
  peeracle::PeerInterface *_peerA;
  peeracle::PeerInterface *_peerB;
};

class MyPeerBSessionDescriptionObserver :
  public peeracle::PeerInterface::SessionDescriptionObserver {
 public:
  explicit MyPeerBSessionDescriptionObserver(peeracle::PeerInterface *peerA,
                                             peeracle::PeerInterface *peerB) :
    _peerA(peerA), _peerB(peerB) {

  }

  void onCreateSuccess(const std::string &sdp, const std::string &type) {
    std::cout << "PeerB " << std::hex << _peerB << " created answer" <<
    std::endl;

    MyPeerASessionDescriptionObserver *peerAAnswerObserver = new
      MyPeerASessionDescriptionObserver(_peerA, _peerB);

    std::cout << "PeerA " << std::hex << _peerA << " setting answer" <<
    std::endl;
    _peerA->setAnswer(sdp, peerAAnswerObserver);
  }

  void onSetSuccess() {

  }

  void onCreateFailure(const std::string &error) {

  }

  void onSetFailure(const std::string &error) {

  }

 protected:
  ~MyPeerBSessionDescriptionObserver() {

  }

 private:
  peeracle::PeerInterface *_peerA;
  peeracle::PeerInterface *_peerB;
};

MyPeerASessionDescriptionObserver::MyPeerASessionDescriptionObserver(
  peeracle::PeerInterface *peerA, peeracle::PeerInterface *peerB) :
  _peerA(peerA), _peerB(peerB) {

}

void MyPeerASessionDescriptionObserver::onCreateSuccess(
  const std::string &sdp, const std::string &type) {
  MyPeerBSessionDescriptionObserver *obs = new
    MyPeerBSessionDescriptionObserver(_peerA, _peerB);

  std::cout << "PeerA " << std::hex << _peerA << " created offer, sending to "
    "PeerB " << std::hex << _peerB << std::endl;

  _peerB->createAnswer(sdp, obs);
}

void MyPeerASessionDescriptionObserver::onSetSuccess() {
  std::cout << "PeerA " << std::hex << _peerA << " set answer" << std::endl;
}

void MyPeerASessionDescriptionObserver::onCreateFailure(const std::string
                                                        &error) {

}

void MyPeerASessionDescriptionObserver::onSetFailure(const std::string
                                                     &error) {

}

int main(int argc, char **argv) {
  new peeracle::Manager;

  peerA = new peeracle::Peer();
  peerB = new peeracle::Peer();

  MyPeerAObserver *peerAObserver = new MyPeerAObserver();
  MyPeerBObserver *peerBObserver = new MyPeerBObserver();
  MyPeerASessionDescriptionObserver *peerAOfferObserver = new
    MyPeerASessionDescriptionObserver(peerA, peerB);

  peerA->subscribe(peerAObserver);
  peerB->subscribe(peerBObserver);
  peerA->createOffer(peerAOfferObserver);

  while (true) {
    peeracle::Manager::getSingleton().Update();
  }

  //delete peerAObserver;
  //delete peerAOfferObserver;
  //delete peerBObserver;
  //delete peeracle::Manager::getSingletonPtr();
  return EXIT_SUCCESS;
}
