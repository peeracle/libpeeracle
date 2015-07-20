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

#include "samples/vlc-plugin/PeeracleStream.h"

PeeracleStream::PeeracleStream(demux_t *vlc,
                               peeracle::MetadataInterface *metadata) :
  _vlc(vlc), _metadata(metadata), _demuxStream(NULL), _esOut(NULL) {
  vlc_mutex_init(&_lock);
}

PeeracleStream::~PeeracleStream() {
  if (_demuxStream) {
    stream_Delete(_demuxStream);
  }

  if (_esOut) {
    delete _esOut;
  }
}

bool PeeracleStream::init() {
  _esOut = new es_out_t;
  if (!_esOut) {
    return false;
  }

  _pcr = VLC_TS_0;
  _group = 0;

  _esOut->pf_add = esOutAdd;
  _esOut->pf_control = esOutControl;
  _esOut->pf_del = esOutDel;
  _esOut->pf_destroy = esOutDestroy;
  _esOut->pf_send = esOutSend;
  _esOut->p_sys = reinterpret_cast<es_out_sys_t *>(this);

  _demuxStream = stream_DemuxNew(_vlc, "mkv", _esOut);
  return _demuxStream != NULL;
}

PeeracleManagerInterface::Status PeeracleStream::Demux(mtime_t deadline) {
  /*static bool sent = false;

  if (!sent) {
    uint32_t length = _metadata->getStreams()[0]->getInitSegmentLength();
    block_t *block = block_Alloc(length);

    memcpy(block->p_buffer, _metadata->getStreams()[0]->getInitSegment(),
           length);
    block->i_buffer = length;
    stream_DemuxSend(_demuxStream, block);

    sent = true;
    return PeeracleManagerInterface::Status::STATUS_DEMUXED;
  }*/

  return PeeracleManagerInterface::Status::STATUS_BUFFERING;
}

int64_t PeeracleStream::GetDuration() {
  return static_cast<int64_t>(_metadata->getDuration());
}

int PeeracleStream::GetGroup() {
  return _group;
}

bool PeeracleStream::IsLive() {
  return false;
}

bool PeeracleStream::IsSeekable() {
  return true;
}

bool PeeracleStream::SetPosition(int64_t time) {
  return true;
}

es_out_id_t *PeeracleStream::esOutAdd(es_out_t *es,
                                      const es_format_t *fmt) {
  PeeracleStream *me = reinterpret_cast<PeeracleStream *>(es->p_sys);
  msg_Dbg(me->_vlc, "[Peeracle::esOutAdd] start");
  es_out_id_t *p_es = me->_vlc->out->pf_add(me->_vlc->out, fmt);
  /*if (p_es) {
    vlc_mutex_lock(&me->_lock);
    Demuxed *pair = new(std::nothrow) Demuxed();
    if (pair) {
      pair->es_id = p_es;
      me->queues.push_back(pair);
    }
    vlc_mutex_unlock(&me->_lock);
  }*/
  msg_Dbg(me->_vlc, "[Peeracle::esOutAdd] end");
  return p_es;
}

int PeeracleStream::esOutSend(es_out_t *es, es_out_id_t *id, block_t *block) {
  PeeracleStream *me = reinterpret_cast<PeeracleStream *>(es->p_sys);
  msg_Dbg(me->_vlc, "[Peeracle::esOutSend] start");
  /*vlc_mutex_lock(&me->_lock);
  std::list<Demuxed *>::const_iterator it;
  for(it=me->queues.begin(); it!=me->queues.end();++it)
  {
    Demuxed *pair = *it;
    if(pair->es_id == p_es)
    {
      block_ChainLastAppend(&pair->pp_queue_last, p_block);
      break;
    }
  }
  vlc_mutex_unlock(&me->_lock);*/
  msg_Dbg(me->_vlc, "[Peeracle::esOutSend] end");
  return VLC_SUCCESS;
}

void PeeracleStream::esOutDel(es_out_t *es, es_out_id_t *id) {
  PeeracleStream *me = reinterpret_cast<PeeracleStream *>(es->p_sys);
  msg_Dbg(me->_vlc, "[Peeracle::esOutDel] start");
  /*vlc_mutex_lock(&me->lock);
  std::list<Demuxed *>::iterator it;
  for(it=me->queues.begin(); it!=me->queues.end();++it)
  {
    if((*it)->es_id == p_es)
    {
      me->sendToDecoderUnlocked(INT64_MAX - VLC_TS_0);
      delete *it;
      me->queues.erase(it);
      break;
    }
  }
  vlc_mutex_unlock(&me->lock);*/
  me->_vlc->out->pf_del(me->_vlc->out, id);
  msg_Dbg(me->_vlc, "[Peeracle::esOutDel] end");
}

int PeeracleStream::esOutControl(es_out_t *es, int query, va_list args) {
  PeeracleStream *me = reinterpret_cast<PeeracleStream *>(es->p_sys);
  msg_Dbg(me->_vlc, "[Peeracle::esOutControl] start");

  if (query == ES_OUT_SET_PCR) {
    me->_pcr = (int64_t) va_arg(args, int64_t);
    return VLC_SUCCESS;
  } else if (query == ES_OUT_SET_GROUP_PCR) {
    me->_group = static_cast<int>(va_arg(args, int));
    me->_pcr = static_cast<int64_t>(va_arg(args, int64_t));
    return VLC_SUCCESS;
  }

  msg_Dbg(me->_vlc, "[Peeracle::esOutControl] end");
  return me->_vlc->out->pf_control(me->_vlc->out, query, args);
}

void PeeracleStream::esOutDestroy(es_out_t *es) {
  PeeracleStream *me = reinterpret_cast<PeeracleStream *>(es->p_sys);
  msg_Dbg(me->_vlc, "[Peeracle::esOutDestroy]");
  me->_vlc->out->pf_destroy(me->_vlc->out);
}
