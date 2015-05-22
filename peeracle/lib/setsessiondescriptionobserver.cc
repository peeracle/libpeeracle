#include <iostream>
#include "setsessiondescriptionobserver.h"

namespace peeracle {

SetSessionDescriptionObserver::SetSessionDescriptionObserver(
  PeerInterface::SessionDescriptionObserver* observer) : _observer(observer) {

}

void SetSessionDescriptionObserver::OnSuccess() {
  _observer->onSetSuccess();
}

void SetSessionDescriptionObserver::OnFailure(const std::string &error) {
  _observer->onSetFailure(error);
}

}