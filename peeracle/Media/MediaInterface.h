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

#ifndef PEERACLE_MEDIA_MEDIAINTERFACE_H_
#define PEERACLE_MEDIA_MEDIAINTERFACE_H_

#include <stdint.h>
#include <vector>

#include "peeracle/DataStream/DataStreamInterface.h"

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * Media module interface.
 * \addtogroup Media
 */
class MediaInterface {
 public:
  virtual bool Load(DataStreamInterface *dataStream) = 0;

  /**
   * Retrieve the initialization segment.
   * @param out
   */
  virtual void getInitSegment(DataStreamInterface *out) = 0;

  /**
   * Retrieve a media segment by the specified \p timecode.
   * @param timecode
   * @param out
   */
  virtual void getMediaSegment(std::streampos timecode,
                               DataStreamInterface *out) = 0;

  /**
   * Get a list of timecodes.
   */
  virtual const std::vector<uint32_t> &getTimecodes() const = 0;

 protected:
  virtual ~MediaInterface() {}
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_MEDIA_MEDIAINTERFACE_H_
