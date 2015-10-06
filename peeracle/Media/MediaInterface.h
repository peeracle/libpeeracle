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

#include <cstdlib>
#include <ios>

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup Media
 * @{
 * @namespace peeracle::Media
 * @brief Media namespace
 */
namespace Media {

/**
 * Media module interface.
 */
class MediaInterface {
 public:
  /**
   * Retrieve the initialization segment.
   * @param buffer
   * @param length
   */
  virtual void getInitSegment(unsigned char *buffer,
                              std::streamsize length) = 0;

  /**
   * Retrieve a media segment by the specified \p timecode.
   * @param timecode
   * @param buffer
   * @param length
   */
  virtual void getMediaSegment(std::streampos timecode, unsigned char *buffer,
                               std::streamsize length) = 0;

 protected:
  virtual ~MediaInterface() {}
};

/**
 * @}
 */
}  // namespace Media

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_MEDIA_MEDIAINTERFACE_H_
