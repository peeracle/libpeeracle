#ifndef PEERACLE_PEER_PEERCREATESESSIONDESCRIPTIONOBSERVER_H
#define PEERACLE_PEER_PEERCREATESESSIONDESCRIPTIONOBSERVER_H

#include "talk/app/webrtc/jsep.h"
#include "peerinterface.h"

namespace peeracle {

class CreateSessionDescriptionObserver :
  public webrtc::CreateSessionDescriptionObserver {
 public:
  explicit CreateSessionDescriptionObserver(
    PeerInterface::SessionDescriptionObserver* observer);

  void OnSuccess(webrtc::SessionDescriptionInterface* desc);
  void OnFailure(const std::string& error);

 private:
  PeerInterface::SessionDescriptionObserver* _observer;
};

}

#endif
