#ifndef PEERACLE_PEER_PEERINTERFACE_H
#define PEERACLE_PEER_PEERINTERFACE_H

#include <string>

namespace peeracle {

class PeerInterface {
 public:
  class Observer {
   public:
    virtual void onIceCandidate(const std::string &sdpMid,
                                int sdpMLineIndex,
                                const std::string &candidate) = 0;

    virtual void onSignalingChange(int state) = 0;

    virtual void onStateChange(int state) = 0;

    virtual void onIceConnectionChange(int state) = 0;

    virtual void onIceGatheringChange(int state) = 0;

   protected:
    ~Observer() {}
  };

  class SessionDescriptionObserver {
   public:
    virtual void onCreateSuccess(const std::string &sdp,
                                 const std::string &type) = 0;

    virtual void onSetSuccess() = 0;

    virtual void onCreateFailure(const std::string &error) = 0;

    virtual void onSetFailure(const std::string &error) = 0;

   protected:
    ~SessionDescriptionObserver() {}
  };

  virtual void subscribe(PeerInterface::Observer *observer) = 0;

  virtual void unsubscribe(PeerInterface::Observer *observer) = 0;

  virtual void createOffer(SessionDescriptionObserver *observer) = 0;

  virtual bool createAnswer(const std::string &sdp,
                            SessionDescriptionObserver *observer) = 0;

  virtual bool setAnswer(const std::string &sdp,
                         SessionDescriptionObserver *observer) = 0;

  virtual bool addIceCandidate(const std::string &sdpMid,
                               int sdpMLineIndex,
                               const std::string &candidate) = 0;

 protected:
  ~PeerInterface() {}
};

}

#endif
