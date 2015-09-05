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
#include "peeracle/Storage/StorageInterface.h"

using namespace webrtc_jni;

namespace peeracle {

class JNIStorage : public StorageInterface {
 public:
  JNIStorage(JNIEnv *jni, jobject j_Hash)
    : _j_global(jni, j_Hash),
      _j_class(jni, GetObjectClass(jni, j_Hash)) {
  }

  ~JNIStorage() {
  }

  bool retrieve(const std::string &hash, uint32_t segment, uint32_t offset,
                uint32_t length, char *dest) {
    return false;
  }

  bool store(const std::string &hash, uint32_t segment, uint32_t offset,
             uint32_t length, const char *src) {
    return false;
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

#define JOPS(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_Storage_##name

JOPS(jlong, nativeCreateStorage)(JNIEnv *jni, jobject j_this) {
  peeracle::StorageInterface *storage = new peeracle::JNIStorage(jni, j_this);
  return jlongFromPointer(storage);
}

#ifdef __cplusplus
}
#endif
