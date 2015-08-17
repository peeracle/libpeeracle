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

#include "third_party/webrtc/talk/app/webrtc/java/jni/jni_helpers.h"
#include "peeracle/Metadata/Metadata.h"

using webrtc_jni::AttachCurrentThreadIfNeeded;
using webrtc_jni::GetObjectClass;
using webrtc_jni::ScopedGlobalRef;
using webrtc_jni::jlongFromPointer;

namespace peeracle {

class JNIMetadata : public Metadata {
 public:
  JNIMetadata(JNIEnv *jni, jobject j_Metadata)
    : _j_global(jni, j_Metadata),
      _j_class(jni, GetObjectClass(jni, j_Metadata)) {
  }

  ~JNIMetadata() {
  }

 private:
  JNIEnv* jni() {
    return AttachCurrentThreadIfNeeded();
  }

  const ScopedGlobalRef<jobject> _j_global;
  const ScopedGlobalRef<jclass> _j_class;
};

}

#ifdef __cplusplus
extern "C" {
#endif

#define JOPM(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_Metadata_##name

JOPM(jstring, getId)(JNIEnv *, jobject) {
  return NULL;
}

JOPM(jlong, getMagic)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPM(jlong, getVersion)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPM(jstring, getHashAlgorithm)(JNIEnv *, jobject) {
  return NULL;
}

JOPM(jlong, getTimecodeScale)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPM(jdouble, getDuration)(JNIEnv *, jobject) {
  return static_cast<jdouble>(NULL);
}

JOPM(jobject, getTrackerUrls)(JNIEnv *, jobject) {
  return NULL;
}

JOPM(jobject, getStreams)(JNIEnv *, jobject) {
  return NULL;
}

JOPM(void, setHashAlgorithm)(JNIEnv *, jobject, jstring) {
}

JOPM(void, setTimecodeScale)(JNIEnv *, jobject, jlong) {
}

JOPM(void, setDuration)(JNIEnv *, jobject, jdouble) {
}

JOPM(void, addTracker)(JNIEnv *, jobject, jstring) {
}

JOPM(jboolean, serialize)(JNIEnv *, jobject, jobject) {
  return static_cast<jboolean>(NULL);
}

JOPM(jboolean, unserialize)(JNIEnv *, jobject, jobject) {
  return static_cast<jboolean>(NULL);
}

JOPM(jlong, nativeCreateMetadata)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *metadata = new peeracle::JNIMetadata(jni, j_this);
  return jlongFromPointer(metadata);
}

#ifdef __cplusplus
}
#endif
