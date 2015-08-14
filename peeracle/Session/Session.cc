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
#include <vector>
#include <string>

#include "peeracle/Peer/Peer.h"
#include "peeracle/Tracker/Client/TrackerClient.h"

#include "peeracle/Session/Session.h"
#include "peeracle/Session/SessionHandle.h"
#include "peeracle/Session/SessionPeerObserver.h"
#include "peeracle/Session/SessionTrackerClientObserver.h"

namespace peeracle {

Session::Session(SessionObserver *observer) :
  _observer(observer) {
}

Session::~Session() {
}

bool Session::update() {
  for (std::map<std::string, TrackerClientInterface *>::iterator
         it = _trackers.begin();
       it != _trackers.end(); ++it) {
    TrackerClientInterface *tracker = (*it).second;

    tracker->Update();
  }
  return true;
}

SessionHandleInterface *Session::addMetadata(MetadataInterface *metadata,
                                             SessionHandleObserver *observer) {
  SessionHandleInterface *handle;
  SessionTrackerClientObserver *trackerObserver;

  if (_handles.find(metadata->getId()) != _handles.end()) {
    return _handles[metadata->getId()];
  }

  handle = new SessionHandle(metadata, observer);
  _handles[metadata->getId()] = handle;

  std::vector<std::string> &trackers = metadata->getTrackerUrls();
  for (std::vector<std::string>::iterator it = trackers.begin();
       it != trackers.end(); ++it) {
    if (_trackers.find(*it) != _trackers.end()) {
      continue;
    }

    trackerObserver = new SessionTrackerClientObserver(this);
    TrackerClientInterface *tracker = new TrackerClient((*it), trackerObserver);
    trackerObserver->setTrackerClient(tracker);
    if (tracker->Init() && tracker->Connect()) {
      _trackers[(*it)] = tracker;
    }
  }

  (void) _observer;
  return handle;
}

void Session::addPeer(const std::string &id, PeerInterface *peer) {
  _peers[id] = peer;
}

std::map<std::string, SessionHandleInterface *> &Session::getHandles() {
  return _handles;
}

std::map<std::string, PeerInterface *> &Session::getPeers() {
  return _peers;
}

}  // namespace peeracle
