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

  this->file_.read(reinterpret_cast<char*>(*buffer), length);
  std::streamsize s = this->file_.gcount();
  this->file_.seekg(cursor + s);
  return s;
}

std::streamsize FileDataStream::read(int8_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+1 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<int8_t>(buffer), 1);
  this->file_.read(static_cast<int8_t>(buffer), 1);
  this->file_.seekg(cursor+1);
  return 1;
}

std::streamsize FileDataStream::read(uint8_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+1 > this->fileSize_) {
    return 0;
  }

  this->file_.read(static_cast<uint8_t>(buffer), 1);
  this->file_.seekg(cursor+1);
  return 1;
}

std::streamsize FileDataStream::read(int16_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+2 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<int16_t>(buffer), 2);
  this->file_.seekg(cursor+2);
  return 2;
}

std::streamsize FileDataStream::read(uint16_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+2 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<uint16_t>(buffer), 2);
  this->file_.seekg(cursor+2);
  return 2;
}

std::streamsize FileDataStream::read(int32_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<int32_t>(buffer), 4);
  this->file_.seekg(cursor+4);
  return 4;
}

std::streamsize FileDataStream::read(uint32_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<uint32_t>(buffer), 4);
  this->file_.seekg(cursor+4);
  return 4;
}

std::streamsize FileDataStream::read(float *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<float>(buffer), 4);
  this->file_.seekg(cursor+4);
  return 4;
}

std::streamsize FileDataStream::read(double *buffer) {
    if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<double>(buffer), 4);
  this->file_.seekg(cursor+4);
  return 4;
}

std::streamsize FileDataStream::peek(uint8_t **buffer, std::streamsize length) {
    if (!this->file_.is_open() || length < 1) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor + length > this->fileSize_) {
    length = this->fileSize_ - cursor;
  }

  this->file_.read(reinterpret_cast<char*>(*buffer), length);
  return length;
}

std::streamsize FileDataStream::peek(int8_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+1 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<char>(buffer), 1);
  return 1;
}

std::streamsize FileDataStream::peek(uint8_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+1 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<unsigned char>(buffer), 1);
  return 1;
}

std::streamsize FileDataStream::peek(int16_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+2 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<int16_t>(buffer), 2);
  return 2;
}

std::streamsize FileDataStream::peek(uint16_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+2 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<uint16_t>(buffer), 2);
  return 2;
}

std::streamsize FileDataStream::peek(int32_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<int32_t>(buffer), 4);
  return 4;
}

std::streamsize FileDataStream::peek(uint32_t *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<uint32_t>(buffer), 4);
  return 4;
}

std::streamsize FileDataStream::peek(float *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<float>(buffer), 4);
  return 4;
}

std::streamsize FileDataStream::peek(double *buffer) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  if (cursor+4 > this->fileSize_) {
    return 0;
  }

  this->file_.read(reinterpret_cast<double>(buffer), 4);
  return 4;
}

std::streamsize FileDataStream::peek(std::string *buffer) {
  return 0;
}

std::streamsize FileDataStream::write(uint8_t *buffer,
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
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<int8_t>(value));
  return 1;
}

std::streamsize FileDataStream::write(uint8_t value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<unsigned_char>(value));
  return 1;
}

std::streamsize FileDataStream::write(int16_t value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<signed_short>(value));
  return 2;
}

std::streamsize FileDataStream::write(uint16_t value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<unsigned_short>(value));
  return 2;
}

std::streamsize FileDataStream::write(int32_t value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<signed_int>(value));
  return 4;
}

std::streamsize FileDataStream::write(uint32_t value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<unsigned_int>(value));
  return 4;
}

std::streamsize FileDataStream::write(float value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<float>(value));
  return 4;
}

std::streamsize FileDataStream::write(double value) {
  if (!this->file_.is_open()) {
    return 0;
  }

  std::streamsize cursor = this->file_.tellg();
  this->file_.seekp(cursor);
  this->file_.put(reinterpret_cast<double>(value));
  return 4;
}

std::streamsize FileDataStream::write(const std::string &value) {
  return 0;
}

}  // namespace peeracle
