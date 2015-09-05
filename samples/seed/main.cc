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
#include "peeracle/Tracker/Client/TrackerClient.h"
#include "peeracle/DataStream/FileDataStream.h"
#include "peeracle/Metadata/Metadata.h"
#include "peeracle/Session/Session.h"
#include "peeracle/Session/SessionHandle.h"
#include "peeracle/WebSocketsClient/WebSocketsClient.h"
#include "peeracle/peeracle.h"

peeracle::Metadata metadata;
peeracle::Session *session;
peeracle::SessionHandle *sessionHandle;

class MySessionObserver : public peeracle::SessionObserver {
};

class MySessionHandleObserver : public peeracle::SessionHandleObserver {
};

MySessionObserver sessionObserver;
MySessionHandleObserver sessionHandleObserver;

int load_metadata(const std::string &fileName) {
  bool result;
  peeracle::DataStreamInit init;
  peeracle::FileDataStream *file;

  init.path = fileName;
  file = new peeracle::FileDataStream(init);

  if (!file->open()) {
    std::cout << "Can't open the file." << std::endl;
  }
  result = metadata.unserialize(file);
  delete file;

  return result;
}

class TrackerWebSocketsClientObserver :
  public peeracle::WebSocketsClientObserver {
 public:
  TrackerWebSocketsClientObserver() {
  }

  void onConnect() {
  }

  void onMessage(const char *buffer, size_t length) {
  }

  void onDisconnect() {
  }

  void onError() {
  }
};

class MyTrackerClientObserver : public peeracle::TrackerClientObserver {
 public:
  void onConnect(const std::string &id) {
  }

  void onDisconnect() {
  }

  void onConnectionError() {
  }

  void onPeerConnect(const std::string &hash, const std::string &peerId,
                             uint32_t got, bool poke) {
  }

 protected:
  ~MyTrackerClientObserver() { }
};

int main(int argc, char **argv) {
  peeracle::init();

  /*MyTrackerClientObserver *trackerObserver = new MyTrackerClientObserver();
  peeracle::TrackerClientInterface *tracker =
    new peeracle::TrackerClient("ws://127.0.0.1:8080", trackerObserver);

  tracker->Init();
  tracker->Connect();

  while (tracker->Update()) {
  }*/

  if (!load_metadata(argv[1])) {
    std::cout << "Unable to load the metadata file." << std::endl;
    peeracle::cleanup();
    return EXIT_FAILURE;
  }

  session = new peeracle::Session(&sessionObserver);
  session->addMetadata(&metadata, &sessionHandleObserver);

  while (session->update()) {
  }

  peeracle::cleanup();
  return EXIT_SUCCESS;
}
