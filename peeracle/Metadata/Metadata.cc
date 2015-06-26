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

#include "peeracle/Metadata/Metadata.h"

namespace peeracle {

Metadata::Metadata() {
}

bool Metadata::serialize(DataStreamInterface *dataStream) {
  size_t trackersSize;
  if (!this->_trackers.empty() && this->_trackers.size())
    trackersSize = this->_trackers.size();
  else
    trackersSize = 1;
  dataStream->write("PRCL", 4);
  dataStream->write(static_cast<int32_t>(2));
  dataStream->write(_hashAlgorithm);
  dataStream->write(_timeCodeScale);
  dataStream->write(_duration);
  dataStream->write(trackersSize);
  if (!this->_trackers.empty() && this->_trackers.size() > 0) {
    for (int i = 0; i < this->_trackers.size(); i++) {
      dataStream->write(this->_trackers[i]);
    }
  } else {
    dataStream->write("ws://127.0.0.1:8080", 20);
  }
  dataStream->write(0);
  return false;
}

bool Metadata::unserialize(DataStreamInterface *dataStream) {
  uint32_t trackersSize;
  std::string tracker;

  if (dataStream->read(&this->_magic) == -1)
    return false;
  if (dataStream->read(&this->_version) == -1)
    return false;
  if (dataStream->read(&this->_hashAlgorithm) == -1)
    return false;
  if (dataStream->read(&this->_timeCodeScale) == -1)
    return false;
  if (dataStream->read(&this->_duration) == -1)
    return false;
  if (dataStream->read(&trackersSize) == -1)
    return false;
  for (int i=0; i < trackersSize; i++) {
    if (dataStream->read(&tracker) == -1)
      return false;
    this->_trackers.push_back(tracker);
  }
  if (dataStream->read(&this->_streamsNumber) == -1)
    return false;
  return true;
}

uint32_t Metadata::getMagic() {
  return this->_magic;
}

uint32_t Metadata::getVersion() {
  return this->_version;
}

const std::string &Metadata::getHashAlgorithm() {
  return this->_hashAlgorithm;
}

uint32_t Metadata::getTimecodeScale() {
  return this->_timeCodeScale;
}

double Metadata::getDuration() {
  return this->_duration;
}

std::vector<std::string> &Metadata::getTrackers() {
  return _trackers;
}

std::vector<MetadataStreamInterface *> &Metadata::getStreams() {
  return _streams;
}

void Metadata::setHashAlgorithm(const std::string &hashAlgorithm) {
  this->_hashAlgorithm = hashAlgorithm;
}

void Metadata::setTimecodeScale(uint32_t timecodeScale) {
  this->_timeCodeScale = timecodeScale;
}

void Metadata::setDuration(double duration) {
  this->_duration = duration;
}

void Metadata::addTracker(const std::string &tracker) {
  this->_trackers.push_back(tracker);
}
}  // namespace peeracle
