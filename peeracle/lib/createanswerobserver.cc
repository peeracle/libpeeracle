#include <webrtc/base/scoped_ref_ptr.h>
#include "createanswerobserver.h"
#include "setanswerobserver.h"

namespace peeracle {

CreateAnswerObserver::CreateAnswerObserver(rtc::scoped_refptr
    <webrtc::PeerConnectionInterface> peer,
  PeerInterface::SessionDescriptionObserver * obs)
  : _peer(peer), _observer(obs) {

}

void CreateAnswerObserver::OnSuccess(
  webrtc::SessionDescriptionInterface *desc) {
  std::string sdp;

  desc->ToString(&sdp);
  rtc::scoped_refptr <SetAnswerObserver> setAnswerObserver =
    new rtc::RefCountedObject<SetAnswerObserver>(_observer, sdp);

  _peer->SetLocalDescription(setAnswerObserver, desc);
}

void CreateAnswerObserver::OnFailure(const std::string &error) {

}

}