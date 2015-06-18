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

#include <string.h>
#include "peeracle/DataStream/FileDataStream.h"

namespace peeracle {

FileDataStream::FileDataStream(const DataStreamInit &dsInit)
  : filename_(dsInit.path), readOnly_(true) { }

bool FileDataStream::open() {
  this->file_.open(this->filename_.c_str(), std::ifstream::binary);

  if (!this->file_.is_open()) {
    return false;
  }

  std::streamsize tmp = this->file_.tellg();
  this->file_.seekg(0, std::ios::end);
  this->fileSize_ = static_cast<std::streamsize>
    (this->file_.tellg()) - tmp;
  this->file_.seekg(0, std::ios::beg);
  return true;
}

void FileDataStream::close() {
  if (!this->file_.is_open()) {
    return;
  }

  this->file_.close();
}

std::streamsize FileDataStream::seek(std::streamsize offset) {
  if (!this->file_.is_open()) {
    return 0;
  }

  if (offset > this->fileSize_) {
    this->file_.seekg(this->fileSize_);
    return this->file_.tellg();
  }

  this->file_.seekg(offset);
  return this->file_.tellg();
}

std::streamsize FileDataStream::length() const {
  return this->fileSize_;
}

std::streamsize FileDataStream::tell() const {
  //  std::streamsize cursor = this->file_.tellg();
  return 0;
}

std::streamsize FileDataStream::read(uint8_t *buffer,
                                     std::streamsize length) {
  if (!this->file_.is_open() || length < 1) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor + length > this->fileSize_) {
    length = this->fileSize_ - cursor;
  }

  this->file_.read(reinterpret_cast<char*>(buffer), length);
  std::streamsize s = this->file_.gcount();
  this->file_.seekg(cursor + s);
  return s;
}

std::streamsize FileDataStream::read(int8_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(uint8_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(int16_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(uint16_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(int32_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(uint32_t *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(float *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(double *buffer) {
  return this->_read(buffer);
}

std::streamsize FileDataStream::read(std::string *buffer) {
  return 0;
}

template<typename T>
std::streamsize FileDataStream::_read(T *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize length = static_cast<std::streamsize>(sizeof(T));
  std::streamsize cursor = this->file_.tellg();
  if (cursor + length > this->fileSize_) {
    length =  this->fileSize_ - cursor;
  }
  this->file_.read(reinterpret_cast<char*>(buffer), length);
  this->file_.seekg(cursor+length);
  return length;
}

std::streamsize FileDataStream::peek(uint8_t *buffer, std::streamsize length) {
    if (!this->file_.is_open() || length < 1) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor + length > this->fileSize_) {
    length = this->fileSize_ - cursor;
  }

  this->file_.read(reinterpret_cast<char*>(buffer), length);
  return length;
}

std::streamsize FileDataStream::peek(int8_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(uint8_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(int16_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(uint16_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(int32_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(uint32_t *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(float *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(double *buffer) {
  return this->_peek(buffer);
}

std::streamsize FileDataStream::peek(std::string *buffer) {
  return 0;
}

template<typename T>
std::streamsize FileDataStream::_peek(T *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize length = static_cast<std::streamsize>(sizeof(T));
  std::streamsize cursor = this->file_.tellg();
  if (cursor + length > this->fileSize_) {
    length =  this->fileSize_ - cursor;
  }
  this->file_.read(reinterpret_cast<char*>(buffer), length);
  return length;
}

std::streamsize FileDataStream::write(const char *buffer,
                                      std::streamsize length) {
  if  (!this->file_.is_open()) {
  return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.write(buffer, length);
  return length;
}

std::streamsize FileDataStream::write(int8_t value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(uint8_t value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(int16_t value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(uint16_t value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(int32_t value) {
  return  this->_write(value);
}

std::streamsize FileDataStream::write(uint32_t value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(float value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(double value) {
  return this->_write(value);
}

std::streamsize FileDataStream::write(const std::string &value) {
  return this->write(value.c_str(), strlen(value.c_str()) + 1);
}

template<typename T>
std::streamsize FileDataStream::_write(T buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.write(reinterpret_cast<const char*>(&buffer), sizeof(T));
  return sizeof(T);
}

}  // namespace peeracle
