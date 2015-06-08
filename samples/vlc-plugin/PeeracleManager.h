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

#include "peeracle/DataStream/DataStreamInterface.h"
#include "samples/vlc-plugin/PeeracleManagerInterface.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>
#include <vlc_stream.h>

#ifndef VLC_DEMUXER_EOF
# define VLC_DEMUXER_EOF 0
#endif

#ifndef VLC_DEMUXER_EGENERIC
# define VLC_DEMUXER_EGENERIC -1
#endif

#ifndef VLC_DEMUXER_SUCCESS
# define VLC_DEMUXER_SUCCESS 1
#endif

class PeeracleManager : public PeeracleManagerInterface {
 public:
  explicit PeeracleManager(stream_t *stream);
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
  stream_t *_metadataStream;
  peeracle::DataStreamInterface *_metadataDataStream;
};

#endif  // SAMPLES_VLCPLUGIN_PEERACLEMANAGER_H_
