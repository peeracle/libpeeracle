#ifndef PEERACLE_PEER_SETREMOTEOFFEROBSERVER_H
#define PEERACLE_PEER_SETREMOTEOFFEROBSERVER_H

#include <talk/app/webrtc/jsep.h>
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peerinterface.h"

namespace peeracle {

class SetRemoteOfferObserver :
  public webrtc::SetSessionDescriptionObserver {
 public:
  explicit SetRemoteOfferObserver(rtc::scoped_refptr
                                  <webrtc::PeerConnectionInterface> peer,
                                  PeerInterface::SessionDescriptionObserver*
                                  obs);

  void OnSuccess();
  void OnFailure(const std::string& error);

 private:
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer;
  PeerInterface::SessionDescriptionObserver* _observer;
};

}

#endif
