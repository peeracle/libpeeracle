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

#include <iostream>
#include "peeracle/peeracle.h"
#include "peeracle/Session/Session.h"
#include "samples/vlc-plugin/PeeracleManager.h"
#include "samples/vlc-plugin/PeeracleStream.h"
#include "samples/vlc-plugin/VLCDataStream.h"
#include "samples/vlc-plugin/VLCSessionHandleObserver.h"

PeeracleManager::PeeracleManager(demux_t *demux) : _stream(NULL),
                                                   _initialized(false),
                                                   _vlc(demux),
                                                   _metadata(NULL),
                                                   _metadataDataStream(NULL),
                                                   _session(NULL),
                                                   _sessionObserver(NULL),
                                                   _handleObserver(NULL) {
}

PeeracleManager::~PeeracleManager() {
  if (_initialized) {
    peeracle::cleanup();
    _initialized = false;
  }

  if (_sessionObserver) {
    delete _sessionObserver;
  }

  if (_session) {
    delete _session;
  }
}

bool PeeracleManager::Init() {
  stream_t *metadataStream = this->_vlc->s;

  this->_metadataDataStream = new VLCDataStream(metadataStream);
  this->_metadata = new peeracle::Metadata();

  if (!this->_metadata->unserialize(this->_metadataDataStream)) {
    return false;
  }

  this->_stream = new PeeracleStream(this->_vlc, this->_metadata);
  return this->_stream->init();
}

int PeeracleManager::Control(int i_query, va_list args) {
  switch (i_query) {
    case DEMUX_GET_POSITION: {
      if (!_stream->GetDuration()) {
        return VLC_EGENERIC;
      }

      *(va_arg(args, double *)) = static_cast<double>(_vlc->p_sys->currentTime)
                                   / _stream->GetDuration();
      return VLC_SUCCESS;
    }
    case DEMUX_SET_POSITION: {
      int64_t time = _stream->GetDuration() * va_arg(args, double);

      if (!_stream->GetDuration() || !_stream->SetPosition(time)) {
        return VLC_EGENERIC;
      }

      _vlc->p_sys->currentTime = time;
      return VLC_SUCCESS;
    }
    case DEMUX_CAN_CONTROL_PACE:
      *(va_arg(args, bool *)) = true;
      return VLC_SUCCESS;
    case DEMUX_GET_LENGTH:
      *(va_arg(args, int64_t *)) = _stream->GetDuration();
      return VLC_SUCCESS;
    case DEMUX_GET_TIME:
      *(va_arg(args, int64_t *)) = _vlc->p_sys->currentTime;
      return VLC_SUCCESS;
    case DEMUX_SET_TIME: {
      int64_t time = va_arg(args, int64_t);

      if (!_stream->SetPosition(time)) {
        return VLC_EGENERIC;
      }

      _vlc->p_sys->currentTime = time;
      return VLC_SUCCESS;
    }
    case DEMUX_GET_META: {
      vlc_meta_t *p_meta = va_arg(args, vlc_meta_t *);
      vlc_meta_t *meta = vlc_meta_New();

      if (meta == NULL) {
        return VLC_EGENERIC;
      }

      vlc_meta_SetTitle(meta, "Metadata Title");
      vlc_meta_SetPublisher(meta, "Metadata Publisher");
      vlc_meta_SetCopyright(meta, "Metadata Copyright");
      vlc_meta_SetURL(meta, "Metadata URL");

      vlc_meta_Merge(p_meta, meta);
      vlc_meta_Delete(meta);
      return VLC_SUCCESS;
    }
    case DEMUX_CAN_PAUSE:
      *(va_arg(args, bool *)) = !_stream->IsLive();
      return VLC_SUCCESS;
    case DEMUX_CAN_SEEK:
      *(va_arg(args, bool *)) = _stream->IsSeekable();
      return VLC_SUCCESS;
    default:
      break;
  }
  return VLC_EGENERIC;
}

#define DEMUX_INCREMENT (CLOCK_FREQ / 20)

int PeeracleManager::Demux() {
  if (!_initialized) {
    if (!peeracle::init()) {
      return VLC_DEMUXER_EGENERIC;
    }
    _initialized = true;
    return VLC_DEMUXER_SUCCESS;
  }

  if (!_session) {
    msg_Dbg(this->_vlc, "[PeeracleManager::Demux] Initialize a session");
    _sessionObserver = new peeracle::SessionObserver();
    _session = new peeracle::Session(_sessionObserver);
    _handleObserver = new VLCSessionHandleObserver();
    _session->addMetadata(this->_metadata, _handleObserver);
    return VLC_DEMUXER_SUCCESS;
  }

  peeracle::update();
  _session->update();

  Status s = _stream->Demux(_vlc->p_sys->currentTime + DEMUX_INCREMENT);
  switch (s) {
    case Status::STATUS_BUFFERING:
      break;
    case Status::STATUS_EOF:
      return VLC_DEMUXER_EOF;
    case Status::STATUS_DEMUXED:
      /*_vlc->p_sys->currentTime += DEMUX_INCREMENT;
      int group = _stream->GetGroup();
      es_out_Control(_vlc->out, ES_OUT_SET_GROUP_PCR, group,
                     VLC_TS_0 + _vlc->p_sys->currentTime);*/
      break;
  }
  return VLC_DEMUXER_SUCCESS;
}
