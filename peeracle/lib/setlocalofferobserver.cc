#include "setlocalofferobserver.h"

namespace peeracle {

SetLocalOfferObserver::SetLocalOfferObserver(
  PeerInterface::SessionDescriptionObserver* obs, const std::string& sdp)
  : _sdp(sdp), _observer(obs) {

}

void SetLocalOfferObserver::OnSuccess() {
  _observer->onCreateSuccess(_sdp, "offer");
}
void SetLocalOfferObserver::OnFailure(const std::string& error) {

}

}
