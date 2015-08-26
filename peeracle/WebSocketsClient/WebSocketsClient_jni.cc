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

#include <android/log.h>
#include <string>

#include "java/jni/classreferenceholder.h"
#include "third_party/webrtc/webrtc/base/logging.h"
#include "third_party/webrtc/talk/app/webrtc/java/jni/jni_helpers.h"
#include "peeracle/WebSocketsClient/WebSocketsClient.h"

using webrtc_jni::GetEnv;
using webrtc_jni::GetObjectClass;
using webrtc_jni::ScopedGlobalRef;
using webrtc_jni::GetMethodID;
using webrtc_jni::AttachCurrentThreadIfNeeded;
using webrtc_jni::jlongFromPointer;
using webrtc_jni::JavaStringFromStdString;

namespace peeracle {

/*WebSocketsClient::WebSocketsClient(const std::string& url,
                                   WebSocketsClientObserver *observer)
  : _url(url), _observer(observer) {
  // Créer un objet Java org/peeracle/WebSocketsClient
  // Appelle le constructor (methode init)
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "ctor");
  jmethodID m = GetMethodID(jni(), *_j_class, "init", "()J");
  jclass observer_class = FindClass(jni(), "peeracle/WebSocketObserver");
  jmethodID init_observer = GetMethodID(jni(), observer_class, "<init>",
                                         "()V");
  jmethodID add_observer = GetMethodID(jni(), observer_class, "add",
                                        "(Lpeeracle/Object;)Z");
  jobject return_obj = jni()->NewObject(observer_class, init_observer);
  jni()->CallBooleanMethod(return_obj, add_observer, observer);
  return jni()->CallLongMethod(*_j_global, m, JavaStringFromStdString(url),
                               return_obj);
}*/

WebSocketsClient::WebSocketsClient(const std::string &url,
                                   WebSocketsClientObserver *observer)
  : _url(url), _observer(observer),
    _j_class(GetEnv(), FindClass(GetEnv(), "org/peeracle/WebSocketsClient")),
    _j_init(GetMethodID(GetEnv(),  *_j_class, "<init>",
      "(Ljava/lang/String;J)V")),
    _j_global(GetEnv(), GetEnv()->NewObject(*_j_class, _j_init,
      JavaStringFromStdString(GetEnv(), url), jlongFromPointer(observer))){
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "ctor");
}

WebSocketsClient::~WebSocketsClient() {
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "dtor");
}

bool WebSocketsClient::Init() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "init",
                            "()B");
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "Init");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool WebSocketsClient::Connect() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "connect",
                            "()B");
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "Connect");
  return  GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool WebSocketsClient::Update() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "update",
                            "()B");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

bool WebSocketsClient::Send(const char *buffer, size_t length) {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "send",
                            "(C;I)B");
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "Send");
  return GetEnv()->CallBooleanMethod(*_j_global, m, buffer, length);
}

bool WebSocketsClient::Disconnect() {
  jmethodID m = GetMethodID(GetEnv(),  *_j_class, "disconnect",
                            "()B");
  __android_log_write(ANDROID_LOG_DEBUG, "WebSocketsClient", "Disconnect");
  return GetEnv()->CallBooleanMethod(*_j_global, m);
}

}  // namespace peeracle

#ifdef __cplusplus
extern "C" {
#endif

#define JOPWO(rettype, name) \
  rettype JNIEXPORT JNICALL \
  Java_org_peeracle_WebSocketsClient_00024Observer_##name

JOPWO(void, onConnect)(JNIEnv *, jobject) {
}

JOPWO(void, onMessage)(JNIEnv *, jobject, jbyteArray, jlong) {
}

JOPWO(void, onDisconnect)(JNIEnv *, jobject) {
}

JOPWO(void, onError)(JNIEnv *, jobject) {
}

#ifdef __cplusplus
}
#endif
