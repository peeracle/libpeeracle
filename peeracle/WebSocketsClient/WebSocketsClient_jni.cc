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

#include <string.h>
#include <string>

#include "java/jni/classreferenceholder.h"
#include "java/jni/jni_helpers.h"
#include "third_party/webrtc/webrtc/base/logging.h"
#include "peeracle/WebSocketsClient/WebSocketsClient_jni.h"

namespace peeracle {

JNIWebSocketsClient::JNIWebSocketsClient(const std::string &url,
                                   WebSocketsClientObserver *observer)
  : _j_class(GetEnv(), FindClass(GetEnv(), "org/peeracle/WebSocketsClient")),
    _j_init(GetMethodID(GetEnv(),  *_j_class, "<init>",
      "(Ljava/lang/String;J)V")),
    _j_global(GetEnv(), GetEnv()->NewObject(*_j_class, _j_init,
      JavaStringFromStdString(GetEnv(), url), jlongFromPointer(observer))) {
}

JNIWebSocketsClient::~JNIWebSocketsClient() {
}

bool JNIWebSocketsClient::Init() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "init", "()Z");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool JNIWebSocketsClient::Connect() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "connect", "()Z");
  return  GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool JNIWebSocketsClient::Update() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "update", "()Z");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool JNIWebSocketsClient::Send(const char *buffer, size_t length) {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "send", "([BJ)Z");
  jbyteArray j_byteArray = GetEnv()->NewByteArray(static_cast<jsize>(length));
  jlong j_length = static_cast<jlong>(length);
  GetEnv()->SetByteArrayRegion(j_byteArray, 0, static_cast<jsize>(length),
                               reinterpret_cast<const jbyte*>(buffer));

  jboolean ret = GetEnv()->CallBooleanMethod(*_j_global, m, j_byteArray,
                                             j_length);
  GetEnv()->DeleteLocalRef(j_byteArray);

  return ret != 0;
}

bool JNIWebSocketsClient::Disconnect() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "disconnect", "()Z");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

}  // namespace peeracle

#ifdef __cplusplus
extern "C" {
#endif

#define JOPWO(rettype, name) \
  rettype JNIEXPORT JNICALL \
  Java_org_peeracle_WebSocketsClient_00024Observer_##name

static peeracle::WebSocketsClientObserver*
  ExtractNativeWebSocketsClientObserver(JNIEnv* jni,
                                        jobject j_WebSocketsClientObserver) {
  jfieldID native_WebSocketsClientObserver_id =
    GetFieldID(jni, GetObjectClass(jni, j_WebSocketsClientObserver),
               "nativeWebSocketConnectionObserver", "J");
  jlong j_p = GetLongField(jni, j_WebSocketsClientObserver,
                           native_WebSocketsClientObserver_id);
  return reinterpret_cast<peeracle::WebSocketsClientObserver*>(j_p);
}

JOPWO(void, onConnect)(JNIEnv *jni, jobject j_this) {
  peeracle::WebSocketsClientObserver *w =
    ExtractNativeWebSocketsClientObserver(jni, j_this);
  w->onConnect();
}

JOPWO(void, onMessage)(JNIEnv *jni, jobject j_this, jbyteArray j_byteArray,
                       jlong length) {
  peeracle::WebSocketsClientObserver *w =
    ExtractNativeWebSocketsClientObserver(jni, j_this);
  jbyte *bytes = jni->GetByteArrayElements(j_byteArray, NULL);
  char * buffer = new char[length];
  memcpy(buffer, bytes, static_cast<size_t>(length));
  w->onMessage(buffer, static_cast<size_t>(length));
  delete[] buffer;
}

JOPWO(void, onDisconnect)(JNIEnv *jni, jobject j_this) {
  peeracle::WebSocketsClientObserver *w =
    ExtractNativeWebSocketsClientObserver(jni, j_this);
  w->onDisconnect();
}

JOPWO(void, onError)(JNIEnv *jni, jobject j_this) {
  peeracle::WebSocketsClientObserver *w =
    ExtractNativeWebSocketsClientObserver(jni, j_this);
  w->onError();
}

#ifdef __cplusplus
}
#endif
