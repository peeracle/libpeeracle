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

#ifndef PEERACLE_SESSION_SESSIONHANDLEINTERFACE_H_
#define PEERACLE_SESSION_SESSIONHANDLEINTERFACE_H_

#include <string>
#include <vector>

namespace peeracle {

class MetadataInterface;
class PeerInterface;
class SessionHandleInterface {
 public:
  virtual MetadataInterface *getMetadata() const = 0;
  virtual const std::vector<uint32_t> &getGot() const = 0;
  virtual void onPeerEntered(PeerInterface *peer,
                             const std::vector<uint32_t> &got) = 0;
  virtual void onPeerConnected(PeerInterface *peer) = 0;
  virtual void onPeerChunk(PeerInterface *peer, const std::string &hash,
                           uint32_t segment, uint32_t chunk, uint32_t offset,
                           uint32_t length, const char *bytes) = 0;

  virtual void requestSegment(uint32_t segment) = 0;
  virtual ~SessionHandleInterface() {}

  struct Request {
    std::string hash;
    uint32_t segment;
    uint32_t chunk;
    char *buffer;
    uint32_t offset;
    size_t length;
    uint32_t completed;
    PeerInterface *peer;
  };
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONHANDLEINTERFACE_H_
