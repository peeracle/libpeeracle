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

#ifndef PEERACLE_METADATA_METADATASTREAM_H_
#define PEERACLE_METADATA_METADATASTREAM_H_

#include <string>
#include <vector>
#include "peeracle/Hash/HashInterface.h"
#include "peeracle/Metadata/MetadataStreamInterface.h"

namespace peeracle {

class MetadataStream
  : public MetadataStreamInterface {
 public:
  MetadataStream();

  uint8_t getType();
  const std::string &getMimeType();
  uint32_t getBandwidth();
  int32_t getWidth();
  int32_t getHeight();
  int32_t getNumChannels();
  int32_t getSamplingFrequency();
  uint32_t getChunkSize();
  uint8_t *getInitSegment();
  uint32_t getInitSegmentLength();
  std::vector<MetadataMediaSegmentInterface *> &getMediaSegments();

  bool unserialize(DataStream *dataStream,
                   const std::string &hashName, HashInterface *hash);

 private:
  uint8_t _type;
  std::string _mimeType;
  uint32_t _bandwidth;
  int32_t _width;
  int32_t _height;
  int32_t _numChannels;
  int32_t _samplingFrequency;
  uint32_t _chunkSize;
  uint8_t *_initSegment;
  uint32_t _initSegmentLength;
  std::vector<MetadataMediaSegmentInterface *> _mediaSegments;
};

}  // namespace peeracle

#endif  // PEERACLE_METADATA_METADATASTREAM_H_
