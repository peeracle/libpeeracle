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

#ifndef PEERACLE_TRACKER_CLIENT_TRACKERCLIENT_H_
#define PEERACLE_TRACKER_CLIENT_TRACKERCLIENT_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "peeracle/Tracker/Client/TrackerClientInterface.h"
#include "peeracle/Tracker/Client/TrackerClientObserver.h"
#include "peeracle/Tracker/Message/TrackerMessageInterface.h"
#include "peeracle/WebSocketsClient/WebSocketsClientInterface.h"
#include "peeracle/WebSocketsClient/WebSocketsClientObserver.h"

namespace peeracle {

class TrackerClient
  : public TrackerClientInterface {
 public:
  explicit TrackerClient(const std::string &url,
                         TrackerClientObserver *observer);
  ~TrackerClient();

  bool Init();
  bool Connect();
  bool Update();
  const std::string &getUrl() const;
  void announce(const std::string &id, const std::vector<uint32_t> &got);
  void sendSdp(const std::string &id, const std::string &hash,
               const std::string &sdp, const std::string &type);
  void sendIceCandidate(const std::string &id, const std::string &hash,
                        const std::string &sdpMid, uint32_t sdpMLineIndex,
                        const std::string &candidate);

  void send(TrackerMessageInterface *message);

  void _send(TrackerMessageInterface *message);

 private:
  const std::string _url;

  TrackerClientObserver *_observer;
  WebSocketsClientObserver *_webSocketsClientObserver;
  WebSocketsClientInterface *_webSocketsClient;
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_CLIENT_TRACKERCLIENT_H_
