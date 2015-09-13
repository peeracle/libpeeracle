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

#include "java/jni/jni_helpers.h"
#include "peeracle/Metadata/MetadataStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#define JOPMS(rettype, name) \
  rettype JNIEXPORT JNICALL Java_org_peeracle_MetadataStream_##name

JOPMS(jchar, getType)(JNIEnv *, jobject) {
  return static_cast<jchar>(NULL);
}

JOPMS(jstring, getMimeType)(JNIEnv *, jobject) {
  return NULL;
}

JOPMS(jlong, getBandwidth)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPMS(jint, getWidth)(JNIEnv *, jobject) {
  return static_cast<jint>(NULL);
}

JOPMS(jint, getHeight)(JNIEnv *, jobject) {
  return static_cast<jint>(NULL);
}

JOPMS(jint, getNumChannels)(JNIEnv *, jobject) {
  return static_cast<jint>(NULL);
}

JOPMS(jint, getSamplingFrequency)(JNIEnv *, jobject) {
  return static_cast<jint>(NULL);
}

JOPMS(jlong, getChunkSize)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPMS(jbyteArray, getInitSegment)(JNIEnv *, jobject) {
  return NULL;
}

JOPMS(jlong, getInitSegmentLength)(JNIEnv *, jobject) {
  return static_cast<jlong>(NULL);
}

JOPMS(jobject, getMediaSegments)(JNIEnv *, jobject) {
  return NULL;
}

JOPMS(jboolean, unserialize)(JNIEnv *, jobject, jobject, jstring, jobject) {
  return static_cast<jboolean>(NULL);
}

#ifdef __cplusplus
}
#endif
