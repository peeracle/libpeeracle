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

#include "samples/vlc-plugin/VLCSessionHandleObserver.h"

VLCSessionHandleObserver::VLCSessionHandleObserver() {
}

VLCSessionHandleObserver::~VLCSessionHandleObserver() {
}

void VLCSessionHandleObserver::onEnter(peeracle::PeerInterface *peer) {
}

void VLCSessionHandleObserver::onLeave(peeracle::PeerInterface *peer) {
}

void VLCSessionHandleObserver::onRequest(peeracle::PeerInterface *peer,
                                         uint32_t segment, uint32_t chunk) {
}

void VLCSessionHandleObserver::onChunk(peeracle::PeerInterface *peer,
                                       uint32_t segment, uint32_t chunk,
                                       uint32_t offset, const char *bytes,
                                       uint32_t length) {
}

void VLCSessionHandleObserver::onMediaSegment(uint32_t segment,
                                              const char *bytes,
                                              uint32_t length) {
}

void VLCSessionHandleObserver::setSessionHandle
  (peeracle::SessionHandleInterface *handle) {
  _handle = handle;
}
