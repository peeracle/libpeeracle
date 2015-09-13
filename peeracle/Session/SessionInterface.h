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

#ifndef PEERACLE_SESSION_SESSIONINTERFACE_H_
#define PEERACLE_SESSION_SESSIONINTERFACE_H_

#include <map>
#include <string>
#include "peeracle/Storage/StorageInterface.h"
#include "peeracle/Metadata/MetadataInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Session/SessionHandleObserver.h"

namespace peeracle {

class SessionInterface {
 public:
  virtual bool update() = 0;
  virtual SessionHandleInterface *addMetadata(MetadataInterface *metadata,
    SessionHandleObserver *observer) = 0;

  virtual void addPeer(const std::string &id, PeerInterface *peer) = 0;

  virtual std::map<std::string, PeerInterface *> &getPeers() = 0;
  virtual std::map<std::string, SessionHandleInterface *> &getHandles() = 0;

  virtual StorageInterface *getStorage() = 0;

  virtual ~SessionInterface() {}
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONINTERFACE_H_
