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

#ifndef PEERACLE_PEER_PEERINTERFACE_H_
#define PEERACLE_PEER_PEERINTERFACE_H_

#include <map>
#include <string>
#include <vector>
#include "peeracle/Peer/PeerMessageInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"

namespace peeracle {

class PeerInterface {
 public:
  class Observer {
   public:
    virtual void onConnect() = 0;
    virtual void onDisconnect() = 0;
    virtual void onChunk(const std::string &hash, uint32_t segment,
                         uint32_t chunk, uint32_t offset, uint32_t length,
                         const char *bytes) = 0;
    virtual void onMessage(PeerMessageInterface *message) = 0;

   protected:
    virtual ~Observer() {}
  };

  class PeerConnectionObserver {
   public:
    virtual void onIceCandidate(const std::string &sdpMid,
                                int sdpMLineIndex,
                                const std::string &candidate) = 0;
    virtual void onSignalingChange(int state) = 0;
    virtual void onStateChange(int state) = 0;
    virtual void onIceConnectionChange(int state) = 0;
    virtual void onIceGatheringChange(int state) = 0;
    virtual void onMessage(PeerMessageInterface *message,
                           DataStream *dataStream) = 0;

   protected:
    virtual ~PeerConnectionObserver() {}
  };

  class CreateSDPObserver {
   public:
    virtual void onCreateSDPSuccess(const std::string &sdp,
                           const std::string &type) = 0;
    virtual void onCreateSDPFailure(const std::string &error) = 0;

   protected:
    ~CreateSDPObserver() {}
  };

  class SetSDPObserver {
   public:
    virtual void onSetSDPSuccess() = 0;
    virtual void onSetSDPFailure(const std::string &error) = 0;

   protected:
    ~SetSDPObserver() {}
  };

  virtual void addHash(const std::string &hash,
                       const std::vector<uint32_t> &got) = 0;
  virtual const std::map<std::string, std::vector<uint32_t>> &getHashes()
    const = 0;
  virtual const std::string &getId() const = 0;
  virtual SessionHandleInterface::Request *getRequest() const = 0;
  virtual void sendRequest(SessionHandleInterface::Request *request) = 0;

  virtual void processSdp(const std::string &type, const std::string &sdp) = 0;
  virtual void processIceCandidate(const std::string &candidate,
                                   const std::string &sdpMid,
                                   uint32_t sdpMLineIndex) = 0;

  virtual ~PeerInterface() {}
};

}  // namespace peeracle

#endif  // PEERACLE_PEER_PEERINTERFACE_H_
