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

#ifndef SAMPLES_VLCPLUGIN_PEERACLEMANAGER_H_
#define SAMPLES_VLCPLUGIN_PEERACLEMANAGER_H_

#include "samples/vlc-plugin/plugin.h"
#include "peeracle/DataStream/DataStreamInterface.h"
#include "samples/vlc-plugin/PeeracleManagerInterface.h"

class PeeracleManager : public PeeracleManagerInterface {
 public:
  explicit PeeracleManager(demux_t *demux);
  ~PeeracleManager();

  enum Status {
    STATUS_BUFFERING,
    STATUS_DEMUXED,
    STATUS_EOF
  };

  bool Init();
  int Control(int i_query, va_list args);
  int Demux();

 private:
  demux_t *_vlc;
  peeracle::DataStreamInterface *_metadataDataStream;
};

#endif  // SAMPLES_VLCPLUGIN_PEERACLEMANAGER_H_
