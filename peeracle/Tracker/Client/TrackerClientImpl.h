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

#ifndef PEERACLE_TRACKER_CLIENT_TRACKERCLIENTIMPL_H_
#define PEERACLE_TRACKER_CLIENT_TRACKERCLIENTIMPL_H_

#include <queue>
#include <string>

#include "third_party/libwebsockets/lib/libwebsockets.h"
#include "peeracle/Tracker/Message/TrackerMessageInterface.h"
#include "peeracle/Tracker/Client/TrackerClientObserver.h"

namespace peeracle {

#define MAX_TRACKER_PAYLOAD 32768

class TrackerClient::TrackerClientImpl {
 public:
  explicit TrackerClientImpl(const std::string &url,
                             TrackerClientObserver *observer);
  ~TrackerClientImpl();

  bool Init();
  bool Connect();
  bool Update();
  void Send(TrackerMessageInterface *message);

 protected:
  const std::string _url;
  TrackerClientObserver *_observer;

  struct libwebsocket_context *_context;
  struct libwebsocket *_wsi;
  struct libwebsocket_protocols *_protocols;

  std::queue<TrackerMessageInterface *> _messages;

  struct Userdata {
    TrackerClientImpl *client;
    unsigned char buffer[LWS_SEND_BUFFER_PRE_PADDING +
                         MAX_TRACKER_PAYLOAD +
                         LWS_SEND_BUFFER_POST_PADDING];
  } _userData;

  static int Callback(struct libwebsocket_context *context,
                      struct libwebsocket *wsi,
                      enum libwebsocket_callback_reasons reason,
                      void *user, void *in, size_t len);
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_CLIENT_TRACKERCLIENTIMPL_H_
