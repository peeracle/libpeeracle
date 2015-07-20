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

#include <iostream>
#include "peeracle/Hash/Murmur3Hash.h"
#include "third_party/murmur3/murmur3.h"

namespace peeracle {

Murmur3Hash::Murmur3Hash() {
  DataStreamInit init;

  this->_dataStream = new MemoryDataStream(init);
}

Murmur3Hash::~Murmur3Hash() {
  delete this->_dataStream;
}

void Murmur3Hash::init() {
}

void Murmur3Hash::update(DataStreamInterface *dataStream) {
  char *buffer = new char[dataStream->length()];

  dataStream->read(buffer, dataStream->length());
  this->_dataStream->write(buffer, dataStream->length());
  delete buffer;
}

void Murmur3Hash::update(const uint8_t *buffer, size_t length) {
  this->_dataStream->write(reinterpret_cast<const char *>(buffer), length);
}

void Murmur3Hash::final(uint8_t *result) {
  const std::streamsize length = this->_dataStream->length();
  char *buffer = new char[length];
  uint8_t output[16];

  this->_dataStream->seek(0);
  this->_dataStream->read(buffer, length);

  MurmurHash3_x86_128(buffer, static_cast<int>(length), 0x5052434C, output);

  for (int i = 0; i < 16; i += 4) {
    result[i + 0] = output[i + 3];
    result[i + 1] = output[i + 2];
    result[i + 2] = output[i + 1];
    result[i + 3] = output[i + 0];
  }

  delete buffer;
}

void Murmur3Hash::checksum(DataStreamInterface *dataStream, uint8_t *result) {
  this->update(dataStream);
  this->final(result);
}

}

}  // namespace peeracle
