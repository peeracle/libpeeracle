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
#include "samples/vlc-plugin/VLCDataStream.h"
#include "samples/vlc-plugin/plugin.h"

VLCDataStream::VLCDataStream(stream_t *stream) : _stream(stream),
                                                 _bigEndian(true) {
}

std::streamsize VLCDataStream::length() {
  return static_cast<std::streamsize>(stream_Size(this->_stream));
}

std::streamsize VLCDataStream::seek(std::streamsize offset) {
  return stream_Seek(this->_stream, static_cast<uint64_t>(offset));
}

std::streamsize VLCDataStream::tell() {
  return static_cast<std::streamsize>(stream_Tell(this->_stream));
}

std::streamsize VLCDataStream::vread(char *buffer,
                                    std::streamsize length) {
  return stream_Read(this->_stream, buffer, static_cast<int>(length));
}


std::streamsize VLCDataStream::vpeek(char *buffer, std::streamsize length) {
  int ret;
  const uint8_t *peek;

  ret = stream_Peek(this->_stream, &peek, static_cast<int>(length));
  memcpy(buffer, peek, static_cast<size_t>(length));
  return ret;
}

std::streamsize VLCDataStream::vwrite(const char *buffer,
                                     std::streamsize length) {
  return 0;
}
