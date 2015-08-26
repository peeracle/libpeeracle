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

#include "peeracle/Metadata/Metadata.h"
#include "java/jni/classreferenceholder.h"
#include "peeracle/Peer/Peer.h"
#include "third_party/webrtc/talk/app/webrtc/java/jni/jni_helpers.h"
#include "peeracle/Session/Session.h"

using namespace webrtc_jni;

namespace peeracle {

class JNIPeer
  : public Peer {
 public:
  JNIPeer(JNIEnv *jni, jobject j_PeerInterface, const std::string &id,
                   TrackerClientInterface *tracker,
                   PeerInterface::Observer *observer)
    : Peer(id, tracker, observer),
      _j_global(jni, j_PeerInterface),
      _j_class(jni, GetObjectClass(jni, j_PeerInterface)) {
  }

  ~JNIPeer() {
  }

 private:
  const ScopedGlobalRef<jobject> _j_global;
  const ScopedGlobalRef<jclass> _j_class;
};

class JNISessionHandleObserver : public SessionHandleObserver {
 public:
  JNISessionHandleObserver(JNIEnv *jni, jobject j_Observer)
    : _j_global(jni, j_Observer),
      _j_class(jni, GetObjectClass(jni, j_Observer)) {
  }

  ~JNISessionHandleObserver() {
  }

 private:
  const ScopedGlobalRef<jobject> _j_global;
  const ScopedGlobalRef<jclass> _j_class;
};

class JNISessionObserver : public SessionObserver {
 public:
  JNISessionObserver(JNIEnv *jni, jobject j_Observer)
    : _j_global(jni, j_Observer),
      _j_class(jni, GetObjectClass(jni, j_Observer)) {
  }

  ~JNISessionObserver() {
  }

 private:
  const ScopedGlobalRef<jobject> _j_global;
  const ScopedGlobalRef<jclass> _j_class;
};

class JNISession : public Session {
 public:
  JNISession(JNIEnv *jni, jobject j_Session, SessionObserver *observer)
    : Session(observer),
      _j_global(jni, j_Session),
      _j_class(jni, GetObjectClass(jni, j_Session)) {
  }

  ~JNISession() {
  }

 private:
  const ScopedGlobalRef<jobject> _j_global;
  const ScopedGlobalRef<jclass> _j_class;
};

}

#ifdef __cplusplus
extern "C" {
#endif

#define JOPS(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_Session_##name

static peeracle::Session *ExtractNativeSession(
  JNIEnv* jni, jobject j_Session) {
  jfieldID native_Session_id =
    GetFieldID(jni, GetObjectClass(jni, j_Session), "nativeSession", "J");
  jlong j_p = GetLongField(jni, j_Session, native_Session_id);
  return reinterpret_cast<peeracle::Session*>(j_p);
}

static peeracle::Peer *ExtractNativePeer(JNIEnv *jni, jobject j_Peer) {
  jfieldID native_Peer_id =
    GetFieldID(jni, GetObjectClass(jni, j_Peer), "nativePeer", "J");
  jlong j_p = GetLongField(jni, j_Peer, native_Peer_id);
  return reinterpret_cast<peeracle::Peer*>(j_p);
}

static peeracle::Metadata *ExtractNativeMetadata(
  JNIEnv* jni, jobject j_Metadata) {
  jfieldID native_Metadata_id =
    GetFieldID(jni,GetObjectClass(jni, j_Metadata), "nativeMetadata", "J");
  jlong j_p = GetLongField(jni, j_Metadata, native_Metadata_id);
  return reinterpret_cast<peeracle::Metadata*>(j_p);
}

JOPS(jboolean, update)(JNIEnv *jni, jobject j_this) {
  peeracle::Session *s = ExtractNativeSession(jni, j_this);
  return static_cast<jboolean>(s->update());
}

JOPS(jobject, addMetadata)(JNIEnv *jni, jobject j_this, jobject j_metadata,
                           jobject j_sessionHandleObserver) {
  //  Crée un JNISessionHandleObserver, stockes-y j_sessionHandleObserver
  //  Extrais metadata
  //  Extrais Session
  //  Appelle addMetadata avec le metadata et le nouveau JNISessionHandleObserver
  // - Cet appel retourne un SessionHandle
  // - Crée un nouvel objet Java org/peeracle/SessionHandle
  // - Modifie le field nativeSessionHandle avec l'adresse du SessionHandle
  // retourné précédemment
  // - Retourne le nouvel objet Java
  peeracle::Session *s = ExtractNativeSession(jni, j_this);
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_metadata);
  peeracle::SessionHandleObserver *sessionHandleObserver =
    new peeracle::JNISessionHandleObserver(jni, j_sessionHandleObserver);
  jclass sessionHandle_class = FindClass(jni, "org/peeracle/SessionHandle");
  jmethodID init_sessionHandle = GetMethodID(jni, sessionHandle_class, "<init>",
                                              "()V");
  jfieldID  fieldId = GetFieldID(jni, sessionHandle_class,
                                 "nativeSessionHandle", "J");
  jobject return_obj = jni->NewObject(sessionHandle_class, init_sessionHandle);
  SetLongField(jni, return_obj, fieldId,
               jlongFromPointer(s->addMetadata(m, sessionHandleObserver)));
  return return_obj;
}

JOPS(void, addPeer)(JNIEnv *jni, jobject j_this, jstring j_id, jobject j_peer) {
  peeracle::Session *s = ExtractNativeSession(jni, j_this);
  peeracle::PeerInterface *peer = ExtractNativePeer(jni, j_peer);
  s->addPeer(JavaToStdString(jni, j_id), peer);
}

JOPS(jobject, getPeers)(JNIEnv *jni, jobject j_this) {
  peeracle::Session *s = ExtractNativeSession(jni, j_this);
  std::map<std::string, peeracle::PeerInterface*>& map =
    (std::map<std::string, peeracle::PeerInterface*> &) s->getPeers();
  jclass map_class = FindClass(jni, "java/util/Map");
  jmethodID init_map = GetMethodID(jni, map_class, "<init>",
                                         "()V");
  jmethodID add_map = GetMethodID(jni, map_class, "add",
                                        "(Ljava/lang/Map;)Z");
  jobject return_obj = jni->NewObject(map_class, init_map);

  for(std::map<std::string, peeracle::PeerInterface*>::iterator it = map.begin()
    ; it != map.end(); ++it) {
    jclass peerInterface_class = FindClass(jni, "org/peeracle/Peer");
    jmethodID init_peerInterface = GetMethodID(jni, peerInterface_class,
                                              "<init>",
                                               "()V");
    jfieldID  fieldId = GetFieldID(jni, peerInterface_class,
                                   "nativePeer", "J");
    jobject j_peerInterface = jni->NewObject(peerInterface_class,
                                        init_peerInterface);
    SetLongField(jni, j_peerInterface, fieldId,
                 jlongFromPointer((*it).second));
    jni->CallBooleanMethod(return_obj, add_map, j_peerInterface);
  }
  return return_obj;
}

JOPS(jobject, getHandles)(JNIEnv *, jobject) {
  return NULL;
}

/*
 * Class:     org_peeracle_Session
 * Method:    nativeCreateSession
 * Signature: (J)J
 */
JOPS(jlong, nativeCreateSession)(JNIEnv *jni, jobject j_this,
                                 jlong j_nativeObserver) {
  peeracle::SessionObserver *observer =
    reinterpret_cast<peeracle::SessionObserver *>(j_nativeObserver);
  peeracle::Session *session = new peeracle::JNISession(jni, j_this, observer);
  return jlongFromPointer(session);
}

/*
 * Class:     org_peeracle_Session
 * Method:    nativeCreateSessionObserver
 * Signature: (Lorg/peeracle/Session/Observer;)J
 */
JOPS(jlong, nativeCreateSessionObserver)(JNIEnv *jni, jobject j_this,
                                  jobject j_Observer) {
  peeracle::SessionObserver *observer =
    new peeracle::JNISessionObserver(jni, j_Observer);
  return jlongFromPointer(observer);
}

#ifdef __cplusplus
}
#endif
