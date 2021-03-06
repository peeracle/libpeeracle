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

#ifndef PEERACLE_SESSION_SESSION_H_
#define PEERACLE_SESSION_SESSION_H_

#include <map>
#include <string>

#include "peeracle/Peer/PeerInterface.h"
#include "peeracle/Session/SessionInterface.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Session/SessionObserver.h"
#include "peeracle/Storage/StorageInterface.h"
#include "peeracle/Tracker/Client/TrackerClientInterface.h"

namespace peeracle {

class Session
  : public SessionInterface {
 public:
  explicit Session(StorageInterface *storage, SessionObserver *observer);
  ~Session();

  bool update();
  SessionHandleInterface *addMetadata(MetadataInterface *metadata,
                                      SessionHandleObserver *observer);

  std::map<std::string, PeerInterface *> &getPeers();
  std::map<std::string, SessionHandleInterface *> &getHandles();
  StorageInterface *getStorage();

 private:
  StorageInterface *_storage;
  SessionObserver *_observer;
  std::map<std::string, PeerInterface *> _peers;
  std::map<std::string, SessionHandleInterface *> _handles;
  std::map<std::string, TrackerClientInterface *> _trackers;
 public:
  virtual void addPeer(const std::string &id, PeerInterface *peer);
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSION_H_
