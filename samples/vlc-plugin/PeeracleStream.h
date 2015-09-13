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

#ifndef SAMPLES_VLC_PLUGIN_PEERACLESTREAM_H_
#define SAMPLES_VLC_PLUGIN_PEERACLESTREAM_H_

#include <list>
#include "peeracle/Metadata/MetadataInterface.h"
#include "samples/vlc-plugin/plugin.h"
#include "samples/vlc-plugin/PeeracleStreamInterface.h"

class PeeracleStream :
  public PeeracleStreamInterface {
 public:
  explicit PeeracleStream(demux_t *vlc,
                          peeracle::MetadataInterface *metadata);
  ~PeeracleStream();

  bool init();
  PeeracleManagerInterface::Status Demux(mtime_t deadline);
  int64_t GetDuration();
  int GetGroup();
  mtime_t GetPCR() const;
  bool IsLive();
  bool IsSeekable();
  bool SetPosition(int64_t time);

  void PushBlock(block_t *block);

 private:
  demux_t *_vlc;
  peeracle::MetadataInterface *_metadata;
  stream_t *_demuxStream;
  es_out_t *_esOut;
  vlc_mutex_t _lock;

  mtime_t _pcr;
  int _group;

  class Demuxed {
    friend class PeeracleStream;
    Demuxed();
    ~Demuxed();
    void drop();
    es_out_id_t *es_id;
    block_t  *p_queue;
    block_t **pp_queue_last;
  };
  std::list<Demuxed *> queues;

  void sendToDecoderUnlocked(mtime_t nzdeadline);

  static es_out_id_t *esOutAdd(es_out_t *es, const es_format_t *fmt);
  static int esOutSend(es_out_t *es, es_out_id_t *id, block_t *block);
  static void esOutDel(es_out_t *es, es_out_id_t *id);
  static int esOutControl(es_out_t *es, int query, va_list args);
  static void esOutDestroy(es_out_t *es);
};

#endif  // SAMPLES_VLC_PLUGIN_PEERACLESTREAM_H_
