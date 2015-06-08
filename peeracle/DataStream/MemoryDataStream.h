/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of int8_tge, to any person obtaining a copy
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

#ifndef PEERACLE_DATASTREAM_MEMORYDATASTREAM_H_
#define PEERACLE_DATASTREAM_MEMORYDATASTREAM_H_

#include <string>
#include "peeracle/DataStream/DataStreamInterface.h"

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup DataStream
 * DataStream module interface.
 */
class MemoryDataStream : public DataStreamInterface {
 public:
  explicit MemoryDataStream(const uint8_t *buffer, uint32_t length);
  virtual ~MemoryDataStream() {}

  bool open();
  void close();
  std::streamsize length() const;
  std::streamsize seek(std::streamsize offset);
  std::streamsize tell() const;

  std::streamsize read(uint8_t **buffer, std::streamsize length);
  std::streamsize read(int8_t *buffer);
  std::streamsize read(uint8_t *buffer);
  std::streamsize read(int16_t *buffer);
  std::streamsize read(uint16_t *buffer);
  std::streamsize read(int32_t *buffer);
  std::streamsize read(uint32_t *buffer);
  std::streamsize read(float *buffer);
  std::streamsize read(double *buffer);

  std::streamsize peek(uint8_t **buffer, std::streamsize length);
  std::streamsize peek(int8_t *buffer);
  std::streamsize peek(uint8_t *buffer);
  std::streamsize peek(int16_t *buffer);
  std::streamsize peek(uint16_t *buffer);
  std::streamsize peek(int32_t *buffer);
  std::streamsize peek(uint32_t *buffer);
  std::streamsize peek(float *buffer);
  std::streamsize peek(double *buffer);

  std::streamsize write(uint8_t **buffer, std::streamsize length);
  std::streamsize write(int8_t value);
  std::streamsize write(uint8_t value);
  std::streamsize write(int16_t value);
  std::streamsize write(uint16_t value);
  std::streamsize write(int32_t value);
  std::streamsize write(uint32_t value);
  std::streamsize write(float buffer);
  std::streamsize write(double buffer);

 protected:
  uint8_t *_buffer;
  uint32_t _length;
  uint32_t _cursor;
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_DATASTREAM_MEMORYDATASTREAM_H_
