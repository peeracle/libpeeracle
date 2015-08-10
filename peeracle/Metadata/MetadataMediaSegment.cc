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

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "peeracle/Hash/Murmur3Hash.h"
#include "peeracle/Metadata/MetadataMediaSegment.h"

namespace peeracle {

MetadataMediaSegment::MetadataMediaSegment() {
}

uint32_t MetadataMediaSegment::getTimecode() {
  return _timecode;
}

uint32_t MetadataMediaSegment::getLength() {
  return _length;
}

const std::vector<uint8_t *> &MetadataMediaSegment::getChunks() {
  return _chunks;
}

bool MetadataMediaSegment::unserialize(DataStream *dataStream,
                                       const std::string &hashAlgorithm,
                                       HashInterface *hash) {
  uint32_t chunkCount;

  if (dataStream->read(&_timecode) == -1 ||
    dataStream->read(&_length) == -1 || dataStream->read(&chunkCount) == -1) {
    return false;
  }

  if (hashAlgorithm != "murmur3_x86_128") {
    return false;
  }

  for (uint32_t c = 0; c < chunkCount; ++c) {
    uint8_t *chunk = new uint8_t[16];

    Murmur3Hash::unserialize(dataStream, chunk);
    _chunks.push_back(chunk);
    hash->update(chunk, 16);
  }

  return true;
}

}  // namespace peeracle
