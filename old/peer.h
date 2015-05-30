#ifndef PEERACLE_PEER_PEER_H
#define PEERACLE_PEER_PEER_H

#include <list>
#include "peerinterface.h"

namespace peeracle {

class Peer
  : public PeerInterface {
 public:
  explicit Peer();

  void subscribe(PeerInterface::Observer* observer);
  void unsubscribe(PeerInterface::Observer* observer);

  void createOffer(PeerInterface::SessionDescriptionObserver* observer);
  bool createAnswer(const std::string &sdp,
                    PeerInterface::SessionDescriptionObserver* observer);

  bool setAnswer(const std::string &sdp,
                 PeerInterface::SessionDescriptionObserver* observer);

  bool addIceCandidate(const std::string &sdpMid,
                       int sdpMLineIndex,
                       const std::string &candidate);

 protected:
  virtual ~Peer();

 private:
  class PeerImpl;
  PeerImpl *peer_;
};

}

#endif
