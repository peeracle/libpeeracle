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

#ifndef PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_H_
#define PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_H_

#include <string>
#include <queue>

#ifdef USE_LIBWEBSOCKETS
#include "third_party/libwebsockets/lib/libwebsockets.h"
#endif
#include "peeracle/WebSocketsClient/WebSocketsClientInterface.h"
#include "peeracle/WebSocketsClient/WebSocketsClientObserver.h"
#ifdef WEBRTC_ANDROID
#include "third_party/webrtc/talk/app/webrtc/java/jni/jni_helpers.h"
using webrtc_jni::ScopedGlobalRef;
#endif

namespace peeracle {

#define MAX_TRACKER_PAYLOAD 32768

class WebSocketsClient : public WebSocketsClientInterface {
 public:
  WebSocketsClient(const std::string& url, WebSocketsClientObserver *observer);
  ~WebSocketsClient();

  bool Init();
  bool Connect();
  bool Update();
  bool Send(const char *buffer, size_t length);
  bool Disconnect();

 private:
  const std::string &_url;
  WebSocketsClientObserver *_observer;

#ifdef USE_LIBWEBSOCKETS
  struct libwebsocket_context *_context;
  struct libwebsocket *_wsi;
  struct libwebsocket_protocols *_protocols;

  struct Message {
    const char *buffer;
    size_t length;
  };

  std::queue<Message *> _messages;

  struct Userdata {
    WebSocketsClient *client;
    unsigned char buffer[LWS_SEND_BUFFER_PRE_PADDING +
                         MAX_TRACKER_PAYLOAD +
                         LWS_SEND_BUFFER_POST_PADDING];
  } _userData;

  static int Callback(struct libwebsocket_context *context,
                      struct libwebsocket *wsi,
                      enum libwebsocket_callback_reasons reason,
                      void *user, void *in, size_t len);
#endif
#ifdef WEBRTC_ANDROID
  const ScopedGlobalRef<jclass> _j_class;
  jmethodID _j_init;
  const ScopedGlobalRef<jobject> _j_global;
#endif
};

}  // namespace peeracle

#endif  // PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_H_
