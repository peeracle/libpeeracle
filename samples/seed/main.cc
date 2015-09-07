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

#include "peeracle/DataStream/FileDataStream.h"
#include "peeracle/Metadata/Metadata.h"
#include "peeracle/Session/SessionHandleInterface.h"
#include "peeracle/Session/SessionHandleObserver.h"
#include "peeracle/Session/SessionObserver.h"
#include "peeracle/Session/Session.h"
#include "peeracle/Storage/MemoryStorage.h"
#include "peeracle/peeracle.h"

peeracle::Metadata metadata;
peeracle::Session *session;
peeracle::SessionHandleInterface *sessionHandle;
peeracle::StorageInterface *storage;

class MySessionObserver
  : public peeracle::SessionObserver {
};

class MySessionHandleObserver
  : public peeracle::SessionHandleObserver {
 public:
  MySessionHandleObserver() {
  }

  ~MySessionHandleObserver() {
  }

  void onEnter(peeracle::PeerInterface *peer) {
  }

  void onLeave(peeracle::PeerInterface *peer) {
  }

  void onRequest(peeracle::PeerInterface *peer, uint32_t segment,
                 uint32_t chunk) {
  }

  void onChunk(peeracle::PeerInterface *peer, uint32_t segment, uint32_t chunk,
               uint32_t offset, const char *bytes, uint32_t length) {
  }

  void onSegment(uint32_t segment, const char *bytes, uint32_t length) {
  }

  void setSessionHandle(peeracle::SessionHandleInterface *handle) {
    _handle = handle;
  }

 private:
  peeracle::SessionHandleInterface *_handle;
};

MySessionObserver sessionObserver;
MySessionHandleObserver *sessionHandleObserver;

bool load_metadata(const std::string &fileName) {
  peeracle::DataStreamInit init;
  init.path = fileName;

  peeracle::FileDataStream file(init);

  if (!file.open()) {
    std::cout << "Can't open the file." << std::endl;
    return false;
  }

  return metadata.unserialize(&file);
}

int main(int argc, char **argv) {
  peeracle::init();

  if (!load_metadata(argv[1])) {
    std::cout << "Unable to load the metadata file." << std::endl;
    peeracle::cleanup();
    return EXIT_FAILURE;
  }

  storage = new peeracle::MemoryStorage();
  session = new peeracle::Session(storage, &sessionObserver);
  sessionHandleObserver = new MySessionHandleObserver();

  sessionHandle = session->addMetadata(&metadata, sessionHandleObserver);
  sessionHandleObserver->setSessionHandle(sessionHandle);

  sessionHandle->requestSegment(0);
  while (peeracle::update() && session->update()) {
  }

  peeracle::cleanup();
  return EXIT_SUCCESS;
}
