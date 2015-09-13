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
#include "peeracle/Hash/HashInterface.h"

using namespace webrtc_jni;

namespace peeracle {

class JNIHash : public HashInterface {
 public:
  JNIHash(JNIEnv *jni, jobject j_Hash)
    : _j_global(jni, j_Hash),
      _j_class(jni, GetObjectClass(jni, j_Hash)) {
  }

  ~JNIHash() {
  }

  void init() {
  }

  void update(DataStream *dataStream) {
  }

  void update(const uint8_t *buffer, size_t length) {
  }

  void update(const char *buffer, size_t length) {
  }

  void final(uint8_t *result) {
  }

  void final(char *result) {
  }

  void checksum(DataStream *dataStream, uint8_t *result) {
  }

  void checksum(DataStream *dataStream, char *result) {
  }

  uint32_t getLength() {
    return 0;
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

#define JOPH(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_Hash_##name

JOPH(jlong, nativeCreateHash)(JNIEnv *jni, jobject j_this) {
  peeracle::HashInterface *hash = new peeracle::JNIHash(jni, j_this);
  return jlongFromPointer(hash);
}

#ifdef __cplusplus
}
#endif
