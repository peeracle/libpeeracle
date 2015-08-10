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

#ifndef PEERACLE_METADATA_METADATASTREAMINTERFACE_H_
#define PEERACLE_METADATA_METADATASTREAMINTERFACE_H_

#include <stdint.h>
#include <ios>
#include <string>
#include <vector>

#include "peeracle/DataStream/DataStream.h"
#include "peeracle/Hash/HashInterface.h"
#include "peeracle/Metadata/MetadataMediaSegmentInterface.h"

namespace peeracle {

class MetadataStreamInterface {
 public:
  virtual uint8_t getType() = 0;
  virtual const std::string &getMimeType() = 0;
  virtual uint32_t getBandwidth() = 0;
  virtual int32_t getWidth() = 0;
  virtual int32_t getHeight() = 0;
  virtual int32_t getNumChannels() = 0;
  virtual int32_t getSamplingFrequency() = 0;
  virtual uint32_t getChunkSize() = 0;
  virtual uint8_t *getInitSegment() = 0;
  virtual uint32_t getInitSegmentLength() = 0;
  virtual std::vector<MetadataMediaSegmentInterface *> &getMediaSegments() = 0;

  virtual bool unserialize(DataStream *dataStream,
                           const std::string &hashName,
                           HashInterface *hash) = 0;

  virtual ~MetadataStreamInterface() {}
};

}  // namespace peeracle

#endif  // PEERACLE_METADATA_METADATASTREAMINTERFACE_H_
