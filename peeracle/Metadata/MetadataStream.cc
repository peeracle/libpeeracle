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

#include <iostream>
#include "peeracle/Metadata/MetadataStream.h"
#include "peeracle/Metadata/MetadataMediaSegment.h"

namespace peeracle {

MetadataStream::MetadataStream() {
}

uint8_t MetadataStream::getType() {
  return _type;
}

const std::string &MetadataStream::getMimeType() {
  return _mimeType;
}

uint32_t MetadataStream::getBandwidth() {
  return _bandwidth;
}

int32_t MetadataStream::getWidth() {
  return _width;
}

int32_t MetadataStream::getHeight() {
  return _height;
}

int32_t MetadataStream::getNumChannels() {
  return _numChannels;
}

int32_t MetadataStream::getSamplingFrequency() {
  return _samplingFrequency;
}

uint32_t MetadataStream::getChunkSize() {
  return _chunkSize;
}

uint8_t *MetadataStream::getInitSegment() {
  return _initSegment;
}

uint32_t MetadataStream::getInitSegmentLength() {
  return _initSegmentLength;
}

std::vector<MetadataMediaSegmentInterface *>
  &MetadataStream::getMediaSegments() {
  return _mediaSegments;
}

bool MetadataStream::unserialize(DataStreamInterface *dataStream,
                                 const std::string &hashName,
                                 HashInterface *hash) {
  uint32_t mediaSegmentCount;
  MetadataMediaSegmentInterface *mediaSegment;

  if (dataStream->read(&this->_type) == -1 ||
      dataStream->read(&this->_mimeType) == -1 ||
      dataStream->read(&this->_bandwidth) == -1 ||
      dataStream->read(&this->_width) == -1 ||
      dataStream->read(&this->_height) == -1 ||
      dataStream->read(&this->_numChannels) == -1 ||
      dataStream->read(&this->_samplingFrequency) == -1 ||
      dataStream->read(&this->_chunkSize) == -1 ||
      dataStream->read(&this->_initSegmentLength) == -1) {
    return false;
  }

  this->_initSegment = new uint8_t[this->_initSegmentLength];
  if (dataStream->read(reinterpret_cast<char *>(this->_initSegment),
                       this->_initSegmentLength) == -1) {
    return false;
  }

  hash->update(this->_initSegment, this->_initSegmentLength);

  if (dataStream->read(&mediaSegmentCount) == -1) {
    return false;
  }

  for (size_t i = 0; i < mediaSegmentCount; ++i) {
    mediaSegment = new MetadataMediaSegment();
    if (!mediaSegment->unserialize(dataStream, hashName, hash)) {
      return false;
    }
    _mediaSegments.push_back(mediaSegment);
  }

  std::cout << "type = " << this->_type << " mimeType = " << this->_mimeType
  << " bandwidth = " << this->_bandwidth << " width = " << this->_width
  << " height = " << this->_height << " numChannels = " << this->_numChannels
  << " samplingFrequency = " << this->_samplingFrequency << " chunksize = "
  << this->_chunkSize << " initSegmentLength = " << this->_initSegmentLength
  << std::endl;
  return true;
}

}  // namespace peeracle
