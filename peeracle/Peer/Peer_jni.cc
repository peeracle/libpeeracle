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
#include "peeracle/Peer/Peer.h"

using namespace webrtc_jni;

#ifdef __cplusplus
extern "C" {
#endif

#define JOPP(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_Peer_##name

JOPP(void, CreateOffer)(JNIEnv *, jobject, jobject) {
}

JOPP(void, CreateAnswer)(JNIEnv *, jobject, jstring, jobject) {
}

JOPP(void, SetAnswer)(JNIEnv *, jobject, jstring, jobject) {
}

JOPP(void, AddICECandidate)(JNIEnv *, jobject, jstring, jint, jstring) {
}

JOPP(jstring, getId)(JNIEnv *, jobject) {
  return NULL;
}

JOPP(jlong, nativeCreatePeer)(JNIEnv *, jobject, jstring, jobject, jobject) {
  return static_cast<jlong>(NULL);
}

#ifdef __cplusplus
}
#endif
