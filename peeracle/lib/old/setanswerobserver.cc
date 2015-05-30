#include "setanswerobserver.h"

namespace peeracle {

SetAnswerObserver::SetAnswerObserver(
  PeerInterface::SessionDescriptionObserver *obs, const std::string &sdp)
  : _observer(obs), _sdp(sdp) {
}

void SetAnswerObserver::OnSuccess() {
  _observer->onCreateSuccess(_sdp, "answer");
}

void SetAnswerObserver::OnFailure(const std::string &error) {
  _observer->onCreateFailure(error);
}

}
