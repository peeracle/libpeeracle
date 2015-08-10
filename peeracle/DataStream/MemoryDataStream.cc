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

#include <cstring>
#include <sstream>
#include "peeracle/DataStream/MemoryDataStream.h"

namespace peeracle {

MemoryDataStream::MemoryDataStream(const DataStreamInit &dsInit) :
  _bigEndian(dsInit.bigEndian), _cursor(0) {
}

MemoryDataStream::~MemoryDataStream() {
  this->_buffer.clear();
}

std::streamsize MemoryDataStream::length() const {
  return this->_buffer.size();
}

std::streamsize MemoryDataStream::seek(std::streamsize position) {
  if (position < 0 ||
      static_cast<std::streamsize>(this->_cursor) +
      position > this->_buffer.size()) {
    return -1;
  }
  this->_cursor = position;
  return this->_cursor;
}

std::streamsize MemoryDataStream::tell() const {
  return this->_cursor;
}

std::streamsize MemoryDataStream::vread(char *buffer,
                                       std::streamsize length) {
  std::streamsize result = this->vpeek(buffer, length);

  if (result > 0) {
    this->_cursor += result;
  }

  return result;
}

std::streamsize MemoryDataStream::vpeek(char *buffer,
                                       std::streamsize length) {
  char *src;
  std::streamsize result = 0;
  size_t size = static_cast<size_t>(length);

  if (static_cast<std::streamsize>(this->_cursor) +
        length > this->_buffer.size()) {
    return -1;
  }

  src = reinterpret_cast<char*>(&this->_buffer[this->_cursor]);
  memcpy(buffer, src, size);

  return length;
}

/*template <typename T>
std::streamsize MemoryDataStream::_peek(T *buffer) {
  T value;
  T finalValue;
  uint8_t *originalData;
  uint8_t *finalData;
  std::streamsize size = static_cast<std::streamsize>(sizeof(T));

  if (static_cast<std::streamsize>(this->_cursor) +
      size > this->_buffer.size()) {
    return -1;
  }

  value = *(reinterpret_cast<T*>(&this->_buffer[this->_cursor]));
  if (_bigEndian && sizeof(T) > 1) {
    originalData = reinterpret_cast<uint8_t*>(&value);
    finalData = reinterpret_cast<uint8_t*>(&finalValue);
    for (int i = 0; i < sizeof(T); ++i) {
      finalData[i] = originalData[(sizeof(T) - i) - 1];
    }
    value = finalValue;
  }

  *buffer = value;
  return sizeof(T);
}*/

std::streamsize MemoryDataStream::vwrite(const char *buffer,
                                         std::streamsize length) {
  size_t pos = static_cast<size_t>(this->_cursor);
  size_t size = static_cast<size_t>(length);

  if (pos + size > this->_buffer.size()) {
    this->_buffer.resize(pos + size);
  }

  memcpy(&this->_buffer[pos], buffer, size);
  this->_cursor += size;
  return size;
}

/*template <typename T>
std::streamsize MemoryDataStream::_write(T value) {
  T finalValue = value;
  uint8_t *originalData = reinterpret_cast<uint8_t*>(&value);
  uint8_t *finalData = reinterpret_cast<uint8_t*>(&finalValue);

  if (_bigEndian && sizeof(T) > 1) {
    for (int i = 0; i < sizeof(T); ++i) {
      finalData[i] = originalData[(sizeof(T) - i) - 1];
    }
    originalData = finalData;
  }

  return this->_write(originalData, sizeof(T));
}*/

}  // namespace peeracle
