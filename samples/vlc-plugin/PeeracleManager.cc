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

#include "samples/vlc-plugin/PeeracleManager.h"
#include "samples/vlc-plugin/VLCStreamDataSource.h"

PeeracleManager::PeeracleManager(stream_t *stream) : _metadataStream(stream) {
}

PeeracleManager::~PeeracleManager() {
}

bool PeeracleManager::Init() {
  this->_metdataDataSource = new VLCStreamDataSource(this->_metadataStream);
  return true;
}

int PeeracleManager::Control(int i_query, va_list args) {
  return VLC_SUCCESS;
}

int PeeracleManager::Demux() {
  return VLC_DEMUXER_SUCCESS;
}
