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

#ifndef PEERACLE_METADATA_METADATA_H_
#define PEERACLE_METADATA_METADATA_H_

#include <string>
#include <vector>
#include "peeracle/Metadata/MetadataInterface.h"

namespace peeracle {

class Metadata : public MetadataInterface {
 public:
  Metadata();

  uint32_t getMagic();
  uint32_t getVersion();
  const std::string &getHashAlgorithm();
  uint32_t getTimecodeScale();
  double getDuration();
  std::vector<std::string> &getTrackers();
  std::vector<MetadataStreamInterface *> &getStreams();

  void setHashAlgorithm(const std::string &hashAlgorithm);
  void setTimecodeScale(uint32_t timecodeScale);
  void setDuration(double duration);
  void addTracker(const std::string &tracker);

  bool serialize(DataStreamInterface *dataStream);
  bool unserialize(DataStreamInterface *dataStream);

 private:
  std::string _empty;
  std::vector<std::string> _trackers;
  std::vector<MetadataStreamInterface *> _streams;
};

}  // namespace peeracle

#endif  // PEERACLE_METADATA_METADATA_H_
