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

#ifndef LIBPEERACLE_DATASTREAM_JNI_H
#define LIBPEERACLE_DATASTREAM_JNI_H

#include <jni.h>
#include "peeracle/DataStream/DataStream.h"

class DataStreamJava : public peeracle::DataStream {
 public:
  DataStreamJava(JNIEnv *jni, jobject dataStreamm);

  jobject getJNIObject() const;
  jclass getJNIClass() const;

  std::streamsize length() const;
  std::streamsize tell() const;
  std::streamsize seek(std::streamsize position);

 private:
  std::streamsize vread(char *buffer, std::streamsize length);
  std::streamsize vpeek(char *buffer, std::streamsize length);
  std::streamsize vwrite(const char *buffer, std::streamsize length);

 private:
  JNIEnv* jni() {
    void* env = NULL;
    g_JVM->GetEnv(&env, JNI_VERSION_1_6);
    return reinterpret_cast<JNIEnv *>(env);
  }

  const jobject j_dataStream_global_;
  const jclass j_dataStream_class_;
};

#endif //LIBPEERACLE_DATASTREAM_JNI_H
