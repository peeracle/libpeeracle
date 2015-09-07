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

#include <map>
#include <string>
#include <vector>

#include "peeracle/Peer/PeerInterface.h"
#include "peeracle/Peer/PeerMessageInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Tracker/Client/TrackerClientInterface.h"

namespace peeracle {

class Peer
  : public PeerInterface, PeerInterface::PeerConnectionObserver,
    PeerInterface::CreateSDPObserver, PeerInterface::SetSDPObserver {
 public:
  explicit Peer(PeerInterface::Observer *observer, const std::string &id,
                TrackerClientInterface *tracker);
  ~Peer();

  enum State {
    Disconnected,
    Connecting,
    Connected
  };

  void CreateOffer(PeerInterface::CreateSDPObserver *createSDPObserver);
  void CreateAnswer(const std::string &sdp,
                    PeerInterface::CreateSDPObserver *createSDPObserver);
  void SetAnswer(const std::string &sdp,
                 PeerInterface::SetSDPObserver *setSDPObserver);
  void AddICECandidate(const std::string &sdpMid, int sdpMLineIndex,
                       const std::string &candidate);

  void onCreateSDPSuccess(const std::string &sdp, const std::string &type);
  void onCreateSDPFailure(const std::string &error);

  void onSetSDPSuccess();
  void onSetSDPFailure(const std::string &error);

  void onIceCandidate(const std::string &sdpMid, int sdpMLineIndex,
                      const std::string &candidate);
  void onSignalingChange(int state);
  void onStateChange(int state);
  void onIceConnectionChange(int state);
  void onIceGatheringChange(int state);
  void onMessage(PeerMessageInterface *message, DataStream *dataStream);

  void addHash(const std::string &hash, const std::vector<uint32_t> &got);
  const std::map<std::string, std::vector<uint32_t>> &getHashes() const;
  const std::string &getId() const;
  SessionHandleInterface::Request *getRequest() const;
  void sendRequest(SessionHandleInterface::Request *request);

  void processSdp(const std::string &type, const std::string &sdp);
  void processIceCandidate(const std::string &candidate,
                           const std::string &sdpMid, uint32_t sdpMLineIndex);

 private:
  class PeerImpl;
  PeerImpl *_peer;

  PeerInterface::Observer *_observer;
  const std::string _id;
  TrackerClientInterface *_tracker;
  SessionHandleInterface::Request *_request;
  State _state;

  std::map<std::string, std::vector<uint32_t>> _hashes;

  void _sendMessage(PeerMessageInterface *message);
};

}  // namespace peeracle

#endif  // PEERACLE_PEER_PEER_H_
