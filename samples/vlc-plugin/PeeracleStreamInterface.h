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

#ifndef SAMPLES_VLC_PLUGIN_PEERACLESTREAMINTERFACE_H_
#define SAMPLES_VLC_PLUGIN_PEERACLESTREAMINTERFACE_H_

#include "samples/vlc-plugin/plugin.h"

class PeeracleStreamInterface {
 public:
  virtual bool init() = 0;
  virtual PeeracleManagerInterface::Status Demux(mtime_t deadline) = 0;
  virtual int64_t GetDuration() = 0;
  virtual int GetGroup() = 0;
  virtual bool IsLive() = 0;
  virtual bool IsSeekable() = 0;
  virtual bool SetPosition(int64_t time) = 0;

  virtual ~PeeracleStreamInterface() { }
};

#endif  // SAMPLES_VLC_PLUGIN_PEERACLESTREAMINTERFACE_H_
