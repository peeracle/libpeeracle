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

#ifndef PEERACLE_SESSION_SESSIONHANDLEOBSERVER_H_
#define PEERACLE_SESSION_SESSIONHANDLEOBSERVER_H_

#include "peeracle/Peer/PeerInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"

namespace peeracle {

class SessionHandleObserver {
 public:
  virtual void onEnter(PeerInterface *peer) = 0;
  virtual void onLeave(PeerInterface *peer) = 0;
  virtual void onRequest(PeerInterface *peer, uint32_t segment,
                         uint32_t chunk) = 0;
  virtual void onChunk(PeerInterface *peer, uint32_t segment, uint32_t chunk,
                       uint32_t offset, const char *bytes, uint32_t length) = 0;
  virtual void onMediaSegment(uint32_t segment, const char *bytes,
                              uint32_t length) = 0;

  virtual ~SessionHandleObserver() { }
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONHANDLEOBSERVER_H_
