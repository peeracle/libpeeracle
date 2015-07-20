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

#ifndef PEERACLE_METADATA_METADATAINTERFACE_H_
#define PEERACLE_METADATA_METADATAINTERFACE_H_

#include <stdint.h>
#include <ios>
#include <string>
#include <vector>
#include "peeracle/DataStream/DataStreamInterface.h"
#include "peeracle/Metadata/MetadataStreamInterface.h"

namespace peeracle {

class MetadataInterface {
 public:
  virtual const std::string &getId() = 0;
  virtual uint32_t getMagic() = 0;
  virtual uint32_t getVersion() = 0;
  virtual const std::string &getHashAlgorithm() = 0;
  virtual uint32_t getTimecodeScale() = 0;
  virtual double getDuration() = 0;
  virtual std::vector<std::string> &getTrackerUrls() = 0;
  virtual std::vector<MetadataStreamInterface *> &getStreams() = 0;

  virtual void setHashAlgorithm(const std::string &hashAlgorithm) = 0;
  virtual void setTimecodeScale(uint32_t timecodeScale) = 0;
  virtual void setDuration(double duration) = 0;
  virtual void addTracker(const std::string &tracker) = 0;

  virtual bool serialize(DataStreamInterface *dataStream) = 0;
  virtual bool unserialize(DataStreamInterface *dataStream) = 0;

  virtual ~MetadataInterface() { }
};

}  // namespace peeracle

#endif  // PEERACLE_METADATA_METADATAINTERFACE_H_
