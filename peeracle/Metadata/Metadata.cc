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
#include <iomanip>
#include <sstream>
#include "peeracle/Hash/Murmur3Hash.h"
#include "peeracle/Metadata/Metadata.h"
#include "peeracle/Metadata/MetadataStream.h"

namespace peeracle {

Metadata::Metadata() {
}

bool Metadata::serialize(DataStreamInterface *dataStream) {
  uint32_t trackersSize;

  if (_trackers.size() > 0) {
    trackersSize = static_cast<uint32_t>(_trackers.size());
  } else {
    trackersSize = 0;
  }

  dataStream->write("PRCL", 4);
  dataStream->write(static_cast<int32_t>(2));
  dataStream->write(_hashAlgorithm);
  dataStream->write(_timeCodeScale);
  dataStream->write(_duration);
  dataStream->write(trackersSize);

  for (size_t i = 0; i < _trackers.size(); i++) {
    dataStream->write(_trackers[i]);
  }

  dataStream->write(0);
  return false;
}

bool Metadata::unserialize(DataStreamInterface *dataStream) {
  HashInterface *hash;
  uint8_t id[16];
  uint32_t trackerCount;
  uint32_t streamCount;
  std::string tracker;
  std::stringstream buffer;
  MetadataStreamInterface *stream;

  if (dataStream->read(&_magic) == -1 ||
    dataStream->read(&_version) == -1 ||
    dataStream->read(&_hashAlgorithm) == -1 ||
    dataStream->read(&_timeCodeScale) == -1 ||
    dataStream->read(&_duration) == -1 ||
    dataStream->read(&trackerCount) == -1) {
    return false;
  }

  if (_hashAlgorithm != "murmur3_x86_128") {
    return false;
  }

  hash = new Murmur3Hash();

  for (size_t i = 0; i < trackerCount; ++i) {
    if (dataStream->read(&tracker) == -1) {
      return false;
    }
    _trackers.push_back(tracker);
  }

  if (dataStream->read(&streamCount) == -1) {
    return false;
  }

  for (size_t i = 0; i < streamCount; ++i) {
    stream = new MetadataStream();
    if (!stream->unserialize(dataStream, _hashAlgorithm, hash)) {
      return false;
    }
    _streams.push_back(stream);
  }

  hash->final(id);
  for (int i = 0; i < 16; ++i) {
    buffer << std::hex << std::setfill('0');
    buffer << std::setw(2)  << static_cast<unsigned>(id[i]);
  }

  _id = buffer.str();
  return true;
}

const std::string &Metadata::getId() {
  return _id;
}

uint32_t Metadata::getMagic() {
  return _magic;
}

uint32_t Metadata::getVersion() {
  return _version;
}

const std::string &Metadata::getHashAlgorithm() {
  return _hashAlgorithm;
}

uint32_t Metadata::getTimecodeScale() {
  return _timeCodeScale;
}

double Metadata::getDuration() {
  return _duration;
}

std::vector<std::string> &Metadata::getTrackerUrls() {
  return _trackers;
}

std::vector<MetadataStreamInterface *> &Metadata::getStreams() {
  return _streams;
}

void Metadata::setHashAlgorithm(const std::string &hashAlgorithm) {
  _hashAlgorithm = hashAlgorithm;
}

void Metadata::setTimecodeScale(uint32_t timecodeScale) {
  _timeCodeScale = timecodeScale;
}

void Metadata::setDuration(double duration) {
  _duration = duration;
}

void Metadata::addTracker(const std::string &tracker) {
  _trackers.push_back(tracker);
}
}  // namespace peeracle
