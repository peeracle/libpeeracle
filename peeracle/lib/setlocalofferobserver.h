#ifndef PEERACLE_PEER_SETLOCALOFFEROBSERVER_H
#define PEERACLE_PEER_SETLOCALOFFEROBSERVER_H

#include "talk/app/webrtc/jsep.h"
#include "peerinterface.h"

namespace peeracle {

class SetLocalOfferObserver :
  public webrtc::SetSessionDescriptionObserver {
 public:
  explicit SetLocalOfferObserver(
    PeerInterface::SessionDescriptionObserver* obs, const std::string& sdp);

  void OnSuccess();
  void OnFailure(const std::string& error);

 private:
  std::string _sdp;
  PeerInterface::SessionDescriptionObserver* _observer;
};

}

#endif