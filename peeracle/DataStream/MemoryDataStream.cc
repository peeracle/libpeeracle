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

#include "peeracle/DataStream/MemoryDataStream.h"

namespace peeracle {

MemoryDataStream::MemoryDataStream(const DataStreamInit &dsInit) {
}

bool MemoryDataStream::open() {
  return false;
}

void MemoryDataStream::close() {
}

std::streamsize MemoryDataStream::length() const {
  return 0;
}

std::streamsize MemoryDataStream::seek(std::streamsize offset) {
  return 0;
}

std::streamsize MemoryDataStream::tell() const {
  return 0;
}

std::streamsize MemoryDataStream::read(uint8_t **buffer,
                                       std::streamsize length) {
  return 0;
}

std::streamsize MemoryDataStream::read(int8_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(uint8_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(int16_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(uint16_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(int32_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(uint32_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(float *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::read(double *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(uint8_t **buffer,
                                       std::streamsize length) {
  return 0;
}

std::streamsize MemoryDataStream::peek(int8_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(uint8_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(int16_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(uint16_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(int32_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(uint32_t *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(float *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::peek(double *buffer) {
  return 0;
}

std::streamsize MemoryDataStream::write(uint8_t **buffer,
                                        std::streamsize length) {
  return 0;
}

std::streamsize MemoryDataStream::write(int8_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(uint8_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(int16_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(uint16_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(int32_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(uint32_t value) {
  return 0;
}

std::streamsize MemoryDataStream::write(float value) {
  return 0;
}

std::streamsize MemoryDataStream::write(double value) {
  return 0;
}

}  // namespace peeracle
