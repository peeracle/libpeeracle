#ifndef PEERACLE_PEER_PEERSETSESSIONDESCRIPTIONOBSERVER_H
#define PEERACLE_PEER_PEERSETSESSIONDESCRIPTIONOBSERVER_H

#include "talk/app/webrtc/jsep.h"
#include "peerinterface.h"

namespace peeracle {

class SetSessionDescriptionObserver :
  public webrtc::SetSessionDescriptionObserver {
 public:
  explicit SetSessionDescriptionObserver(
    PeerInterface::SessionDescriptionObserver* observer);

  void OnSuccess();
  void OnFailure(const std::string& error);

 private:
  PeerInterface::SessionDescriptionObserver* _observer;
};

}

#endif