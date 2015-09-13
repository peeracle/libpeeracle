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

#ifndef PEERACLE_SESSION_SESSIONHANDLE_H_
#define PEERACLE_SESSION_SESSIONHANDLE_H_

#include <string>
#include <map>
#include <vector>

#include "peeracle/Peer/PeerInterface.h"
#include "peeracle/Metadata/MetadataInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Session/SessionHandleObserver.h"
#include "peeracle/Session/SessionInterface.h"

namespace peeracle {

class SessionHandle
  : public SessionHandleInterface {
 public:
  SessionHandle(SessionInterface *session, MetadataInterface *metadata,
                const std::vector<uint32_t> &got,
                SessionHandleObserver *observer);
  ~SessionHandle();

  MetadataInterface *getMetadata() const;
  const std::vector<uint32_t> &getGot() const;

  void onPeerEntered(PeerInterface *peer, const std::vector<uint32_t> &got);
  void onPeerConnected(PeerInterface *peer);
  void onPeerChunk(PeerInterface *peer, const std::string &hash,
                   uint32_t segment, uint32_t chunk, uint32_t offset,
                   uint32_t length, const char *bytes);

  void requestSegment(uint32_t segment);

 private:
  SessionInterface *_session;
  SessionHandleObserver *_observer;
  std::vector<uint32_t> _got;
  MetadataInterface *_metadata;
  std::vector<Request *> _requests;
  std::map<uint32_t, uint32_t> _done;

  void _processRequests();
  void _processRequest(Request *request);
  bool _checkGot(const std::vector<uint32_t> &got, uint32_t segment,
                 uint32_t chunk);
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONHANDLE_H_
