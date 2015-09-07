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
#include <map>
#include <string>
#include <vector>

#include "peeracle/Peer/Peer.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Session/SessionPeerObserver.h"
#include "peeracle/Session/SessionTrackerClientObserver.h"

namespace peeracle {

SessionTrackerClientObserver::SessionTrackerClientObserver(
  SessionInterface * session) : _session(session), _tracker(NULL) {
}

SessionTrackerClientObserver::~SessionTrackerClientObserver() {
}

void SessionTrackerClientObserver::onConnect(const std::string &id) {
  std::cout << "[Session] Connected with id " << id << std::endl;

  std::map<std::string, SessionHandleInterface *> &handles =
    _session->getHandles();

  for (std::map<std::string, SessionHandleInterface *>::iterator mit =
    handles.begin(); mit != handles.end(); ++mit) {
    MetadataInterface *metadata = (*mit).second->getMetadata();
    std::vector<std::string> &trackers = metadata->getTrackerUrls();

    for (std::vector<std::string>::iterator it = trackers.begin();
         it != trackers.end(); ++it) {
      if (_tracker->getUrl() == (*it)) {
        _tracker->announce(metadata->getId(), (*mit).second->getGot());
        break;
      }
    }
  }
}

void SessionTrackerClientObserver::onDisconnect() {
  std::cout << "[Session] Disconnected from tracker" << std::endl;
}

void SessionTrackerClientObserver::onConnectionError() {
  std::cout << "[Session] Error while connecting to the tracker" << std::endl;
}

void SessionTrackerClientObserver::onEnter(const std::string &hash,
                                           const std::string &peerId,
                                           const std::vector<uint32_t> &got) {
  std::map<std::string, PeerInterface *> &peers = _session->getPeers();
  std::map<std::string, SessionHandleInterface *> &handles =
    _session->getHandles();

  if (peers.find(peerId) != peers.end() ||
    handles.find(hash) == handles.end()) {
    return;
  }

  SessionPeerObserver *observer = new SessionPeerObserver(_session);
  PeerInterface *peer = new Peer(observer, peerId, _tracker);
  observer->setPeer(peer);
  peer->addHash(hash, got);

  _session->addPeer(peerId, peer);
  handles[hash]->onPeerEntered(peer, got);
}

void SessionTrackerClientObserver::onSdp(const std::string &id,
                                         const std::string &hash,
                                         const std::string &type,
                                         const std::string &sdp) {
  std::map<std::string, PeerInterface *> &peers = _session->getPeers();

  if (peers.find(id) == peers.end()) {
    return;
  }

  peers[id]->processSdp(type, sdp);
}

void SessionTrackerClientObserver::onIceCandidate(const std::string &id,
                                                  const std::string &hash,
                                                  const std::string &candidate,
                                                  const std::string &sdpMid,
                                                  uint32_t sdpMLineIndex) {
  std::map<std::string, PeerInterface *> &peers = _session->getPeers();

  if (peers.find(id) == peers.end()) {
    return;
  }

  peers[id]->processIceCandidate(candidate, sdpMid, sdpMLineIndex);
}

void SessionTrackerClientObserver::setTrackerClient(
  TrackerClientInterface * tracker) {
  _tracker = tracker;
}

}  // namespace peeracle
