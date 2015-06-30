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

#ifndef PEERACLE_PEER_PEER_H_
#define PEERACLE_PEER_PEER_H_

#include <string>
#include "peeracle/Peer/PeerInterface.h"

namespace peeracle {

class Peer
  : public PeerInterface {
 public:
  explicit Peer(PeerInterface::Observer *observer);
  ~Peer();

  void CreateOffer(PeerInterface::CreateSDPObserver *createSDPObserver);
  void CreateAnswer(const std::string &sdp,
                    PeerInterface::CreateSDPObserver *createSDPObserver);
  void SetAnswer(const std::string &sdp,
                 PeerInterface::SetSDPObserver *setSDPObserver);
  void AddICECandidate(const std::string &sdpMid,
                       int sdpMLineIndex,
                       const std::string &candidate);
 private:
  class PeerImpl;
  PeerImpl *_peer;
};

}  // namespace peeracle

#endif  // PEERACLE_PEER_PEER_H_
