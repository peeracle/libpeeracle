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

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

#include "peeracle/Session/SessionHandle.h"

namespace peeracle {

SessionHandle::SessionHandle(SessionInterface *session,
                             MetadataInterface *metadata,
                             const std::vector<uint32_t> &got,
                             SessionHandleObserver *observer) :
  _session(session), _observer(observer), _got(got), _metadata(metadata) {
  (void)_session;
  (void)_observer;
}

SessionHandle::~SessionHandle() {
  std::vector<char*> buffers;
  std::vector<char*>::iterator bufIt;
  std::vector<Request *>::iterator reqIt;

  for (reqIt = _requests.begin(); reqIt != _requests.end(); ++reqIt) {
    if (std::find(buffers.begin(), buffers.end(), (*reqIt)->buffer) !=
        buffers.end()) {
      buffers.push_back((*reqIt)->buffer);
    }
    delete (*reqIt);
  }

  for (bufIt = buffers.begin(); bufIt != buffers.end(); ++bufIt) {
    delete (*bufIt);
  }
}

MetadataInterface *SessionHandle::getMetadata() const {
  return _metadata;
}

const std::vector<uint32_t> &SessionHandle::getGot() const {
  return _got;
}

void SessionHandle::onPeerEntered(PeerInterface *peer,
                                  const std::vector<uint32_t> &got) {
  std::cout << "[SessionHandle] Peer entered " << peer->getId() <<
  " for hash " << _metadata->getId() << " got " << got.size() << std::endl;

  _processRequests();
}

void SessionHandle::onPeerConnected(PeerInterface *peer) {
  if (peer->getRequest()) {
    peer->sendRequest(peer->getRequest());
  }
}

void hexdump(const void *ptr, int buflen) {
  unsigned char *buf = (unsigned char *) ptr;
  int i, j;
  for (i = 0; i < buflen; i += 16) {
    printf("%06x: ", i);
    for (j = 0; j < 16; j++) {
      if (i + j < buflen) {
        printf("%02x ", buf[i + j]);
      } else {
        printf("   ");
      }
    }
    printf(" ");
    for (j = 0; j < 16; j++) {
      if (i + j < buflen) {
        printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.');
      }
    }
    printf("\n");
  }
}

void SessionHandle::onPeerChunk(PeerInterface *peer, const std::string &hash,
                                uint32_t segment, uint32_t chunk,
                                uint32_t offset, uint32_t length,
                                const char *bytes) {
  std::vector<Request *>::iterator reqIt;

  if (hash != _metadata->getId()) {
    return;
  }

  for (reqIt = _requests.begin(); reqIt != _requests.end(); ++reqIt) {
    Request *request = (*reqIt);

    if (request->hash != hash) {
      continue;
    }

    if (request->segment != segment || request->chunk != chunk) {
      continue;
    }

    std::cout << reinterpret_cast<void*>(bytes[0]) << " " <<
      reinterpret_cast<void*>(bytes[1]) << std::endl;

    memcpy(request->buffer + request->offset + offset, bytes, length);
    request->completed += length;

    if (request->completed < request->length) {
      break;
    }

    std::cout << "chunk complete!" << std::endl;

    MetadataMediaSegmentInterface *seg =
      _metadata->getStreams()[0]->getMediaSegments()[request->segment];
    const char *ch = seg->getChunks()[request->chunk];

    HashInterface *hashAlgorithm = _metadata->getHashAlgorithm();
    uint32_t hashLength = hashAlgorithm->getLength();
    char *result = new char[hashLength];

    hashAlgorithm->init();
    hashAlgorithm->update(request->buffer, request->length);
    hashAlgorithm->final(result);

    if (!memcmp(ch, result, hashLength)) {
      delete[] result;
      std::cout << "checksum is valid" << std::endl;
      return;
    }

    std::cout << "checksum is invalid" << std::endl;
    delete[] result;
    break;
  }
}

void SessionHandle::requestSegment(uint32_t segment) {
  MetadataStreamInterface *stream = _metadata->getStreams()[0];
  const std::vector<MetadataMediaSegmentInterface *> &segments =
    stream->getMediaSegments();

  if (segment > segments.size()) {
    return;
  }

  size_t length = stream->getChunkSize();
  const std::vector<const char*> &chunks = segments[segment]->getChunks();
  char *buffer = new char[segments[segment]->getLength()];

  for (uint32_t i = 0; i < chunks.size(); ++i) {
    Request *request;

    if (i + 1 == chunks.size()) {
      length = stream->getChunkSize() -
               ((stream->getChunkSize() * chunks.size()) -
                segments[segment]->getLength());
    }

    request = new Request;
    request->hash = _metadata->getId();
    request->segment = segment;
    request->chunk = i;
    request->buffer = buffer;
    request->offset = i * stream->getChunkSize();
    request->length = length;
    request->completed = 0;

    std::cout << "Add segment " << segment << " chunk " << i << " " <<
    request->length << std::endl;

    _requests.push_back(request);
  }

  _processRequests();
}

void SessionHandle::_processRequests() {
  std::vector<Request *>::iterator reqIt;
  Request *request;

  std::cout << "_processRequests" << std::endl;
  for (reqIt = _requests.begin(); reqIt != _requests.end(); ++reqIt) {
    request = (*reqIt);

    if (request->completed == request->length || request->peer) {
      continue;
    }

    _processRequest(request);
  }
}

bool SessionHandle::_checkGot(const std::vector<uint32_t> &got,
                              uint32_t segment, uint32_t chunk) {
  MetadataStreamInterface *stream = _metadata->getStreams()[0];
  size_t segmentCount = stream->getMediaSegments().size();
  MetadataMediaSegmentInterface *seg;

  if (segment > segmentCount || !got.size()) {
    return false;
  }

  seg = stream->getMediaSegments()[segment];
  size_t chunkCount = seg->getChunks().size();

  uint32_t gotIndex = 0;
  int gotOffset = 0;

  for (uint32_t si = 0; si < segmentCount; ++si) {
    for (uint32_t ci = 0; ci < chunkCount; ++ci) {
      if (si == segment && ci == chunk) {
        return (got[gotIndex] & (1 << gotOffset)) != 0;
      }
      if (++gotOffset >= 32) {
        if (++gotIndex >= got.size()) {
          return false;
        }
        gotOffset = 0;
      }
    }
  }
  return false;
}

void SessionHandle::_processRequest(Request *request) {
  PeerInterface *peer;
  std::map<std::string, PeerInterface*> &peers = _session->getPeers();
  std::map<std::string, PeerInterface*>::iterator peerIt;

  std::cout << "_processRequest " << request->segment << " " <<
  request->chunk << std::endl;
  for (peerIt = peers.begin(); peerIt != peers.end(); ++peerIt) {
    peer = (*peerIt).second;
    if (peer->getRequest()) {
      std::cout << "peer " << peer->getId() << " has already a request" <<
      std::endl;
      continue;
    }

    const std::map<std::string, std::vector<uint32_t>> &hashes =
      peer->getHashes();
    std::map<std::string, std::vector<uint32_t>>::const_iterator it =
      hashes.find(_metadata->getId());

    if (it == hashes.end()) {
      std::cout << "peer " << peer->getId() << " doesn't have hash" <<
      std::endl;
      continue;
    }

    if (!_checkGot(it->second, request->segment, request->chunk)) {
      std::cout << "peer " << peer->getId() << " doesn't have chunk" <<
      std::endl;
      continue;
    }

    std::cout << "peer " << peer->getId() << " call sendRequest" << std::endl;
    peer->sendRequest(request);
  }
}

}  // namespace peeracle
