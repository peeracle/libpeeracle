#ifndef PEERACLE_PEER_CREATEANSWEROBSERVER_H
#define PEERACLE_PEER_CREATEANSWEROBSERVER_H

#include <talk/app/webrtc/jsep.h>
#include <talk/app/webrtc/peerconnectioninterface.h>
#include "peerinterface.h"

namespace peeracle {

class CreateAnswerObserver :
  public webrtc::CreateSessionDescriptionObserver {
 public:
  explicit CreateAnswerObserver(rtc::scoped_refptr
                                <webrtc::PeerConnectionInterface> peer,
                                PeerInterface::SessionDescriptionObserver *obs);

  void OnSuccess(webrtc::SessionDescriptionInterface* desc);
  void OnFailure(const std::string& error);

 private:
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer;
  PeerInterface::SessionDescriptionObserver* _observer;
};

}

#endif