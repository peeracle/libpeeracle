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

#include <stdint.h>
#include <iostream>
#include <string>
#include "unicode/unistr.h"
#include "java/jni/peeracle_jni.h"
#include "java/jni/datastream_jni.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((visibility("default"))) void
JNICALL Java_org_peeracle_DataStream_nativeCreateDataStream
  (JNIEnv *jni, jobject j_this) {
  DataStreamJava *dataStream = new DataStreamJava(jni, j_this);

  jclass j_datastream_class(jni->GetObjectClass(j_this));
  const jmethodID j_datastream_set_native_datastream(jni->GetMethodID(
    j_datastream_class, "setNativeDataStream", "(J)V"));
  jni->CallVoidMethod(j_this,
                      j_datastream_set_native_datastream,
                      reinterpret_cast<jlong>(dataStream));

  std::cout << "New DataStream created at adr " << dataStream << std::endl;
  dataStream->seek(5);

  /*char buffer[32] = {0};
  dataStream->read(buffer, 22);
  dataStream->read(buffer, 22);
  std::cout << "BUFFER  = " << static_cast<int>(buffer[0]) << ", " <<
    static_cast<int>(buffer[1]) << ", " << static_cast<int>(buffer[2]) <<
    std::endl;
  char c = 'b';
  dataStream->read(&c, 5);
  int8_t i = 2;
  dataStream->read(&i);
  uint8_t j = 2;
  dataStream->read(&j);
  int16_t k = 2;
  dataStream->read(&k);
  uint16_t l = 2;
  dataStream->read(&l);
  int32_t m = 2;
  dataStream->read(&m);
  uint32_t n = 2;
  dataStream->read(&n);
  float o = 2;
  dataStream->read(&o);
  double p = 2;
  dataStream->read(&p);*/
  /*uint8_t j = 2;
  std::cout << "j before = " << static_cast<int32_t>(j) << std::endl;
  dataStream->peek(&j);
  std::cout << "j after = " << static_cast<int32_t>(j) << std::endl;*/
  /*dataStream->peek(&j, 5);
  dataStream->peek(&i);
  dataStream->peek(&j);
  dataStream->peek(&k);
  dataStream->peek(&l);
  dataStream->peek(&m);
  dataStream->peek(&n);
  dataStream->peek(&o);
  dataStream->peek(&p);
  dataStream->write(&c, 5);
  dataStream->write(i);
  dataStream->write(j);
  dataStream->write(k);
  dataStream->write(l);
  dataStream->write(m);
  dataStream->write(n);
  dataStream->write(o);
  dataStream->write(p);
  dataStream->write("hello");
  dataStream->write("hello");*/
}

DataStreamJava::DataStreamJava(JNIEnv *jni, jobject dataStream) :
  j_dataStream_global_(dataStream),
  j_dataStream_class_(jni->GetObjectClass(dataStream)) {
}

std::streamsize DataStreamJava::length() const {
  // jmethodID m = jni()->GetMethodID(j_dataStream_class_,"close", "()"."V");
  // jni()->CallVoidMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::tell() const {
  return 0;
}

std::streamsize DataStreamJava::seek(std::streamsize position) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "seek", "(J)J");
  jni()->CallLongMethod(j_dataStream_global_, m, static_cast<jlong>(position));
  return 0;
}

std::streamsize DataStreamJava::vread(char *buffer, std::streamsize length) {
  jbyteArray jBuff = jni()->NewByteArray(length);
  jni()->SetByteArrayRegion(jBuff, 0, length, reinterpret_cast<const jbyte*>
  (buffer));
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "([BJ)J");
  jni()->CallLongMethod(j_dataStream_global_, m, jBuff, length);
  // jni()->DeleteLocalRef(jBuff);
  return 0;
}

std::streamsize DataStreamJava::vpeek(char *buffer, std::streamsize length) {
  jbyteArray jBuff = jni()->NewByteArray(sizeof(buffer));
  jni()->SetByteArrayRegion(jBuff, 0, sizeof(buffer),
                            reinterpret_cast<const jbyte*>(buffer));
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "([BJ)J");
  jni()->CallLongMethod(j_dataStream_global_, m, jBuff, length);
  return 0;
}

std::streamsize DataStreamJava::vwrite(const char *buffer,
                                       std::streamsize length) {
  jbyteArray jBuff = jni()->NewByteArray(sizeof(buffer));
  jni()->SetByteArrayRegion(jBuff, 0, sizeof(buffer),
                            reinterpret_cast<const jbyte*>(buffer));
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "([BJ)J");
  jni()->CallLongMethod(j_dataStream_global_, m, jBuff, length);
  return 0;
}

#ifdef __cplusplus
}
#endif

/*bool DataStreamJava::open() {
  std::cout << "open: class " << j_dataStream_class_ << std::endl;
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "open", "()Z");
  std::cout << "Open methid id " << m << std::endl;
  if (jni()->ExceptionCheck()) {
    jni()->ExceptionDescribe();
    jni()->ExceptionClear();
  }
  return jni()->CallBooleanMethod(j_dataStream_global_, m);
}

void DataStreamJava::close() {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "close", "()V");
  jni()->CallVoidMethod(j_dataStream_global_, m);
}*/

/*std::streamsize DataStreamJava::read(char *buffer, std::streamsize length) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(int8_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "readChar", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(uint8_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "readByte", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(int16_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(uint16_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(int32_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(uint32_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(float *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(double *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "read", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::read(std::string *buffer) {
  return 0;
}

std::streamsize DataStreamJava::peek(uint8_t *buffer, std::streamsize length) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(int8_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(uint8_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peekByte", "()J");
  jlong result = jni()->CallLongMethod(j_dataStream_global_, m);
  *buffer = static_cast<uint8_t>(result);
  return 1;
}

std::streamsize DataStreamJava::peek(int16_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peekShort", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(uint16_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peekUShort", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(int32_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peekInt", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(uint32_t *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(float *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(double *buffer) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "peek", "()J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::peek(std::string *buffer) {
  return 0;
}

std::streamsize DataStreamJava::write(const char *buffer,
                                      std::streamsize length) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(CJ)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(int8_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(C)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(uint8_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(S)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(int16_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(I)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(uint16_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(J)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(int32_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(J)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(uint32_t value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(J)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(float value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(F)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(double value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(D)J");
  jni()->CallLongMethod(j_dataStream_global_, m);
  return 0;
}

std::streamsize DataStreamJava::write(const std::string &value) {
  jmethodID m = jni()->GetMethodID(j_dataStream_class_,
                                   "write", "(Ljava/lang/String;)J");
  UnicodeString ustr(UnicodeString::fromUTF8(value));
  jstring jstr = jni()->NewString(ustr.getBuffer(), ustr.length());
  jni()->CallLongMethod(j_dataStream_global_, m, jstr);
  return 0;
}
*/
