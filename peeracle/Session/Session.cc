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

#include "peeracle/DataStream/MemoryDataStream.h"

#include "peeracle/Peer/Peer.h"
#include "peeracle/Tracker/Client/TrackerClient.h"

#include "peeracle/Session/Session.h"
#include "peeracle/Session/SessionHandle.h"
#include "peeracle/Session/SessionPeerObserver.h"
#include "peeracle/Session/SessionTrackerClientObserver.h"

namespace peeracle {

Session::Session(StorageInterface *storage, SessionObserver *observer) :
  _storage(storage),
  _observer(observer) {
  (void)_observer;
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
  const std::string &id = metadata->getId();
  SessionHandleInterface *handle;
  HashInterface *hash = metadata->getHashAlgorithm();
  uint32_t hashLen = hash->getLength();
  MetadataStreamInterface *stream = metadata->getStreams()[0];
  std::vector<MetadataMediaSegmentInterface *> &segments =
    stream->getMediaSegments();

  std::vector<uint32_t> got;
  uint32_t gotIndex = 0;
  uint32_t currentGot = 0;

  if (_handles.find(id) != _handles.end()) {
    return _handles[id];
  }

  for (uint32_t i = 0; i < segments.size(); ++i) {
    MetadataMediaSegmentInterface *segment = segments[i];
    char *bytes = new char[segment->getLength()];
    const std::vector<const char *> &chunks = segment->getChunks();

    if (!_storage->retrieve(id, i, 0, segment->getLength(), bytes)) {
      delete[] bytes;
      continue;
    }

    for (uint32_t c = 0; c < chunks.size(); ++c) {
      DataStreamInit init;
      MemoryDataStream *chunkBytes = new MemoryDataStream(init);
      std::streamsize len = stream->getChunkSize();
      char *result = new char[hashLen];

      if (c + 1 == chunks.size()) {
        len = stream->getChunkSize() -
          ((stream->getChunkSize() * chunks.size()) - segment->getLength());
      }

      chunkBytes->write(bytes + (stream->getChunkSize() * c), len);
      chunkBytes->seek(0);

      hash->checksum(chunkBytes, result);
      if (!memcmp(chunks[c], result, hashLen)) {
        currentGot |= (1 << gotIndex);
      }

      if (++gotIndex == 32) {
        got.push_back(currentGot);
        gotIndex = 0;
      }

      delete[] result;
    }

    delete[] bytes;
  }

  handle = new SessionHandle(this, metadata, got, observer);
  _handles[id] = handle;

  std::vector<std::string> &trackers = metadata->getTrackerUrls();
  SessionTrackerClientObserver *trackerObserver;
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
