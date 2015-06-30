/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "peeracle/Peer/Peer.h"
#include "peeracle/peeracle.h"

static peeracle::Peer *peerA;
static peeracle::Peer *peerB;

static bool peerAReady = false;
static bool peerBReady = false;

typedef struct s_iceCandidate {
  std::string sdpMid;
  int sdpMLineIndex;
  std::string candidate;
} t_iceCandidate;

static std::vector<t_iceCandidate> iceCandidatesA;
static std::vector<t_iceCandidate> iceCandidatesB;

class MyPeerObserverA : public peeracle::PeerInterface::Observer {
 public:
  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "[MyPeerObserverA::onIceCandidate] " << candidate << std::endl;

    if (peerBReady) {
      std::cout << "[MyPeerObserverA::onIceCandidate] peerB is ready." <<
        std::endl;
      peerB->AddICECandidate(sdpMid, sdpMLineIndex, candidate);
      return;
    }

    t_iceCandidate ic;
    ic.sdpMid = sdpMid;
    ic.sdpMLineIndex = sdpMLineIndex;
    ic.candidate = candidate;
    iceCandidatesB.push_back(ic);
  }

  void onSignalingChange(int state) {
    std::cout << "[MyPeerObserverA::onSignalingChange] " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "[MyPeerObserverA::onStateChange] " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "[MyPeerObserverA::onIceConnectionChange] " << state <<
      std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "[MyPeerObserverA::onIceGatheringChange] " << state <<
      std::endl;
  }
};

class MySetSDPObserverA : public peeracle::PeerInterface::SetSDPObserver {
 public:
  void onSuccess() {
    std::cout << "[MySetSDPObserverA::onSuccess]" << std::endl;
    peerAReady = true;
    peerBReady = true;

    for (std::vector<t_iceCandidate>::iterator it = iceCandidatesA.begin();
         it != iceCandidatesA.end(); ++it) {
      t_iceCandidate ic = (*it);
      peerA->AddICECandidate(ic.sdpMid, ic.sdpMLineIndex, ic.candidate);
    }

    iceCandidatesA.clear();

    peerBReady = true;
    for (std::vector<t_iceCandidate>::iterator it = iceCandidatesB.begin();
         it != iceCandidatesB.end(); ++it) {
      t_iceCandidate ic = (*it);
      peerB->AddICECandidate(ic.sdpMid, ic.sdpMLineIndex, ic.candidate);
    }

    iceCandidatesB.clear();
  }

  void onFailure(const std::string &error) {
    std::cout << "[MySetSDPObserverA::onFailure] " << error << std::endl;
  }
};

class MyCreateSDPObserverB : public peeracle::PeerInterface::CreateSDPObserver {
 public:
  void onSuccess(const std::string &sdp,
                 const std::string &type) {
    std::cout << "[MyCreateSDPObserverB::onSuccess] type " << type << std::endl;
    std::cout << "SDP data {" << sdp << "}" << std::endl;

    MySetSDPObserverA *setSDPObserverA;
    setSDPObserverA = new MySetSDPObserverA();

    peerA->SetAnswer(sdp, setSDPObserverA);
  }

  void onFailure(const std::string &error) {
    std::cout << "[MyCreateSDPObserverB::onFailure] " << error << std::endl;
  }
};

class MyCreateSDPObserverA : public peeracle::PeerInterface::CreateSDPObserver {
 public:
  void onSuccess(const std::string &sdp,
                 const std::string &type) {
    std::cout << "[MyCreateSDPObserverA::onSuccess] type " << type << std::endl;
    std::cout << "SDP data {" << sdp << "}" << std::endl;

    MyCreateSDPObserverB *createAnswerObserverB;
    createAnswerObserverB = new MyCreateSDPObserverB();

    peerB->CreateAnswer(sdp, createAnswerObserverB);
  }

  void onFailure(const std::string &error) {
    std::cout << "[MyCreateSDPObserverA::onFailure] " << error << std::endl;
  }
};

class MyPeerObserverB : public peeracle::PeerInterface::Observer {
 public:
  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "[MyPeerObserverB::onIceCandidate] " << candidate << std::endl;

    if (peerAReady) {
      std::cout << "[MyPeerObserverB::onIceCandidate] peerA is ready." <<
      std::endl;
      peerA->AddICECandidate(sdpMid, sdpMLineIndex, candidate);
      return;
    }

    t_iceCandidate ic;
    ic.sdpMid = sdpMid;
    ic.sdpMLineIndex = sdpMLineIndex;
    ic.candidate = candidate;
    iceCandidatesA.push_back(ic);
  }

  void onSignalingChange(int state) {
    std::cout << "[MyPeerObserverB::onSignalingChange] " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "[MyPeerObserverB::onStateChange] " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "[MyPeerObserverB::onIceConnectionChange] " << state <<
    std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "[MyPeerObserverB::onIceGatheringChange] " << state <<
    std::endl;
  }
};

int main(int argc, char **argv) {
  peeracle::init();

  MyPeerObserverA *peerObserverA;
  peerObserverA = new MyPeerObserverA();

  MyCreateSDPObserverA *createOfferObserverA;
  createOfferObserverA = new MyCreateSDPObserverA();

  peerA = new peeracle::Peer(peerObserverA);

  MyPeerObserverB *peerObserverB;
  peerObserverB = new MyPeerObserverB();

  peerB = new peeracle::Peer(peerObserverB);
  peerA->CreateOffer(createOfferObserverA);

  while (1) {
    peeracle::update();
  }

  peeracle::cleanup();
  return EXIT_SUCCESS;
}
