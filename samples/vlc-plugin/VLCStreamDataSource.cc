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

#include <vlc_common.h>
#include <vlc_stream.h>
#include "samples/vlc-plugin/VLCStreamDataSource.h"

VLCStreamDataSource::VLCStreamDataSource(stream_t *stream) : _stream(stream) {
}

bool VLCStreamDataSource::open() {
  return true;
}

void VLCStreamDataSource::close() {
  stream_Delete(this->_stream);
}

std::streamsize VLCStreamDataSource::length() const {
  return static_cast<std::streamsize>(stream_Size(this->_stream));
}

std::streamsize VLCStreamDataSource::read(unsigned char *buffer,
                     std::streamsize length) {
  return stream_Read(this->_stream, buffer, static_cast<int>(length));
}

std::streamsize VLCStreamDataSource::seek(std::streamsize offset) {
  return stream_Seek(this->_stream, static_cast<uint64_t>(offset));
}
