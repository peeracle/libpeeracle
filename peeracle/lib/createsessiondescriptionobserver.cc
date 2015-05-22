#include <iostream>
#include <webrtc/base/thread.h>
#include "createsessiondescriptionobserver.h"

namespace peeracle {

CreateSessionDescriptionObserver::CreateSessionDescriptionObserver(
  PeerInterface::SessionDescriptionObserver* observer) : _observer(observer) {

}

void CreateSessionDescriptionObserver::OnSuccess(
  webrtc::SessionDescriptionInterface* desc) {
  std::string sdp;

  desc->ToString(&sdp);
  _observer->onCreateSuccess(sdp, desc->type());
}

void CreateSessionDescriptionObserver::OnFailure(const std::string &error) {
  _observer->onCreateFailure(error);
}

}