#ifndef PEERACLE_PEER_SETANSWEROBSERVER_H
#define PEERACLE_PEER_SETANSWEROBSERVER_H

#include <talk/app/webrtc/jsep.h>
#include "peerinterface.h"

namespace peeracle {

class SetAnswerObserver :
  public webrtc::SetSessionDescriptionObserver {
 public:
  explicit SetAnswerObserver(PeerInterface::SessionDescriptionObserver* obs,
                             const std::string& sdp);

  void OnSuccess();
  void OnFailure(const std::string& error);

 private:
  PeerInterface::SessionDescriptionObserver* _observer;
  std::string _sdp;
};

}

#endif
