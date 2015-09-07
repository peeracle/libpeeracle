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

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "peeracle/Session/SessionPeerObserver.h"

namespace peeracle {

SessionPeerObserver::SessionPeerObserver(SessionInterface *session) :
  _peer(NULL), _session(session) {
  (void) _session;
}

SessionPeerObserver::~SessionPeerObserver() {
}

void SessionPeerObserver::onConnect() {
  std::cout << "[SessionPeerObserver::onConnect]" << std::endl;

  if (!_peer) {
    return;
  }

  std::map<std::string, PeerInterface *> &peers = _session->getPeers();

  if (peers.find(_peer->getId()) == peers.end()) {
    return;
  }

  std::map<std::string, SessionHandleInterface *> &handles =
    _session->getHandles();
  const std::map<std::string, std::vector<uint32_t>> &hashes =
    _peer->getHashes();
  std::map<std::string, std::vector<uint32_t>>::const_iterator it;

  for (it = hashes.begin(); it != hashes.end(); ++it) {
    if (handles.find((*it).first) == handles.end()) {
      continue;
    }

    handles[(*it).first]->onPeerConnected(_peer);
  }
}

void SessionPeerObserver::onDisconnect() {
  std::cout << "[SessionPeerObserver::onDisconnect]" << std::endl;
}

void SessionPeerObserver::onChunk(const std::string &hash, uint32_t segment,
                                  uint32_t chunk, uint32_t offset,
                                  uint32_t length, const char *bytes) {
  std::cout << "[SessionPeerObserver::onChunk] " << segment << " " <<
    chunk << " " << offset << " " << length << std::endl;

  if (!_peer) {
    return;
  }

  std::map<std::string, PeerInterface *> &peers = _session->getPeers();

  if (peers.find(_peer->getId()) == peers.end()) {
    return;
  }

  std::map<std::string, SessionHandleInterface *> &handles =
    _session->getHandles();
  const std::map<std::string, std::vector<uint32_t>> &hashes =
    _peer->getHashes();
  std::map<std::string, std::vector<uint32_t>>::const_iterator it;

  for (it = hashes.begin(); it != hashes.end(); ++it) {
    if (handles.find((*it).first) == handles.end()) {
      continue;
    }

    handles[(*it).first]->onPeerChunk(_peer, hash, segment, chunk, offset,
                                      length, bytes);
  }
}

void SessionPeerObserver::onMessage(PeerMessageInterface *message) {
  std::cout << "[SessionPeerObserver::onMessage]" << std::endl;
}

void SessionPeerObserver::setPeer(PeerInterface *peer) {
  _peer = peer;
}

}  // namespace peeracle
