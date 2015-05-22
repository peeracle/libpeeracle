#include "setremoteofferobserver.h"
#include "createanswerobserver.h"

namespace peeracle {

SetRemoteOfferObserver::SetRemoteOfferObserver(rtc::scoped_refptr
    <webrtc::PeerConnectionInterface> peer,
  PeerInterface::SessionDescriptionObserver * obs)
  : _peer(peer), _observer(obs) {

}

void SetRemoteOfferObserver::OnSuccess() {
  rtc::scoped_refptr <CreateAnswerObserver> createAnswerObserver =
    new rtc::RefCountedObject<CreateAnswerObserver>(_peer, _observer);

  _peer->CreateAnswer(createAnswerObserver, NULL);
}

void SetRemoteOfferObserver::OnFailure(const std::string &error) {

}

}