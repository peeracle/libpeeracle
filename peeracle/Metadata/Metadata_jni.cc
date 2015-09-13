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

#include "java/jni/classreferenceholder.h"
#include "java/jni/jni_helpers.h"
#include "third_party/webrtc/webrtc/base/logging.h"
#include "peeracle/Metadata/Metadata.h"

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

static peeracle::DataStream *ExtractNativeDataStream(
  JNIEnv* jni, jobject j_DataStream) {
  jfieldID native_DataStream_id =
    GetFieldID(jni, GetObjectClass(jni, j_DataStream), "nativeDataStream", "J");
  jlong j_p = GetLongField(jni, j_DataStream, native_DataStream_id);
  return reinterpret_cast<peeracle::DataStream*>(j_p);
}

static peeracle::Metadata *ExtractNativeMetadata(
  JNIEnv* jni, jobject j_Metadata) {
  jfieldID native_Metadata_id =
    GetFieldID(jni,GetObjectClass(jni, j_Metadata), "nativeMetadata", "J");
  jlong j_p = GetLongField(jni, j_Metadata, native_Metadata_id);
  return reinterpret_cast<peeracle::Metadata*>(j_p);
}

JOPM(jstring, getId)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  LOG(LS_INFO) << "Metadata::getId: " << m->getId();
  return JavaStringFromStdString(jni, m->getId());
}

JOPM(jlong, getMagic)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return static_cast<jlong>(m->getMagic());
}

JOPM(jlong, getVersion)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return static_cast<jlong>(m->getVersion());
}

JOPM(jstring, getHashAlgorithmName)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return JavaStringFromStdString(jni, m->getHashAlgorithmName());
}

/*JOPM(jstring, getHashAlgorithm)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return JavaStringFromStdString(jni, m->getHashAlgorithm());
}*/

JOPM(jlong, getTimecodeScale)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return static_cast<jlong>(m->getTimecodeScale());
}

JOPM(jdouble, getDuration)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  return static_cast<jdouble>(m->getDuration());
}


JOPM(jobject, getTrackerUrls)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  std::vector<std::string>& urls = m->getTrackerUrls();
  jclass arraylist_class = FindClass(jni, "java/util/ArrayList");
  jmethodID init_arraylist = GetMethodID(jni, arraylist_class, "<init>",
                                         "()V");
  jmethodID add_arraylist = GetMethodID(jni, arraylist_class, "add",
                                        "(Ljava/lang/Object;)Z");
  jobject return_obj = jni->NewObject(arraylist_class, init_arraylist);

  for(std::vector<std::string>::iterator it = urls.begin(); it != urls.end();
      ++it) {
    jni->CallBooleanMethod(return_obj, add_arraylist, JavaStringFromStdString(
      jni, *it));
  }
  return return_obj;
}

//
JOPM(jobject, getStreams)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  std::vector<peeracle::MetadataStreamInterface*>& dataStreams =
    m->getStreams();
  jclass arraylist_class = FindClass(jni, "java/util/ArrayList");
  jmethodID init_arraylist = GetMethodID(jni, arraylist_class, "<init>",
                                         "()V");
  jmethodID add_arraylist = GetMethodID(jni, arraylist_class, "add",
                                        "(Ljava/lang/Object;)Z");
  jobject return_obj = jni->NewObject(arraylist_class, init_arraylist);

  for(std::vector<peeracle::MetadataStreamInterface*>::iterator it =
    dataStreams.begin();
      it != dataStreams.end(); ++it) {
    jclass metadataStream_class = FindClass(jni, "org/peeracle/MetadataStream");
    jmethodID init_metadataStream = GetMethodID(jni, arraylist_class, "<init>",
                                                "()V");
    jfieldID  fieldId = GetFieldID(jni, metadataStream_class,
                                   "nativeMetadataStream", "J");
    jobject j_MetadataStream = jni->NewObject(metadataStream_class,
                                              init_metadataStream);
    jni->SetLongField(j_MetadataStream,fieldId, jlongFromPointer(*it));
    jni->CallBooleanMethod(return_obj, add_arraylist, j_MetadataStream);
  }
  return return_obj;
}

JOPM(void, setHashAlgorithm)(JNIEnv *jni, jobject j_this, jstring
hashAlgorithm) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  m->setHashAlgorithmName(JavaToStdString(jni, hashAlgorithm));
}

JOPM(void, setTimecodeScale)(JNIEnv *jni, jobject j_this, jlong timecodeScale) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  m->setTimecodeScale(static_cast<long>(timecodeScale));
}

JOPM(void, setDuration)(JNIEnv *jni, jobject j_this, jdouble duration) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  m->setDuration(static_cast<double>(duration));
}

JOPM(void, addTracker)(JNIEnv *jni, jobject j_this, jstring tracker) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  m->addTracker(JavaToStdString(jni, tracker));
}

JOPM(jboolean, serialize)(JNIEnv *jni, jobject j_this, jobject j_dataStream) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  peeracle::DataStream *dataStream = ExtractNativeDataStream(jni, j_dataStream);
  return static_cast<jboolean>(m->serialize(dataStream));
}

JOPM(jboolean, unserialize)(JNIEnv *jni, jobject j_this, jobject j_DataStream) {
  peeracle::Metadata *m = ExtractNativeMetadata(jni, j_this);
  peeracle::DataStream *ds = ExtractNativeDataStream(jni, j_DataStream);
  return static_cast<jboolean>(m->unserialize(ds));
}

JOPM(jlong, nativeCreateMetadata)(JNIEnv *jni, jobject j_this) {
  peeracle::Metadata *metadata = new peeracle::JNIMetadata(jni, j_this);
  return jlongFromPointer(metadata);
}

#ifdef __cplusplus
}
#endif
