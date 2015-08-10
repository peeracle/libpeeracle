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
#include <vector>
#include "peeracle/DataStream/DataStream.h"

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
class MemoryDataStream : public DataStream {
 public:
  explicit MemoryDataStream(const DataStreamInit &dsInit);
  ~MemoryDataStream();

  std::streamsize length() const;
  std::streamsize seek(std::streamsize position);
  std::streamsize tell() const;

 private:
  std::streamsize vread(char *buffer, std::streamsize length);
  std::streamsize vpeek(char *buffer, std::streamsize length);
  std::streamsize vwrite(const char *buffer, std::streamsize length);

 protected:
  bool _bigEndian;
  std::streampos _cursor;
  std::vector<uint8_t> _buffer;
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_DATASTREAM_MEMORYDATASTREAM_H_
