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
#include "peeracle/Hash/Murmur3Hash.h"

using namespace webrtc_jni;

namespace peeracle {

class JNIMurmur3Hash : public Murmur3Hash {
 public:
  JNIMurmur3Hash(JNIEnv *jni, jobject j_Murmur3Hash)
    : _j_global(jni, j_Murmur3Hash),
      _j_class(jni, GetObjectClass(jni, j_Murmur3Hash)) {
  }

  ~JNIMurmur3Hash() {
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
  rettype JNIEXPORT JNICALL Java_org_peeracle_Murmur3Hash_##name

JOPM(void, init)(JNIEnv *, jobject) {
}

JOPM(void, update__Lorg_peeracle_DataStream_2)(JNIEnv *, jobject, jobject) {
}

JOPM(void, update___3BJ)(JNIEnv *, jobject, jbyteArray, jlong) {
}

JOPM(jbyteArray, finish)(JNIEnv *, jobject) {
  return NULL;
}

JOPM(jbyteArray, checksum)(JNIEnv *, jobject, jobject) {
  return NULL;
}

JOPM(jlong, nativeCreateMurmur3Hash)(JNIEnv *env, jobject j_this) {
  peeracle::Murmur3Hash *hash = new peeracle::JNIMurmur3Hash(env, j_this);
  return jlongFromPointer(hash);
}

#ifdef __cplusplus
}
#endif
