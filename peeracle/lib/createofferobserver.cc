#include "createofferobserver.h"
#include "setlocalofferobserver.h"

namespace peeracle {

CreateOfferObserver::CreateOfferObserver(rtc::scoped_refptr
    <webrtc::PeerConnectionInterface> peer,
  PeerInterface::SessionDescriptionObserver * obs)
  : _peer(peer), _observer(obs) {

}

void CreateOfferObserver::OnSuccess(webrtc::SessionDescriptionInterface * desc) {
  std::string sdp;

  desc->ToString(&sdp);
  rtc::scoped_refptr <SetLocalOfferObserver> setLocalOfferObserver =
    new rtc::RefCountedObject<SetLocalOfferObserver>(_observer, sdp);

  _peer->SetLocalDescription(setLocalOfferObserver, desc);
}

void CreateOfferObserver::OnFailure(const std::string &error) {

}

}