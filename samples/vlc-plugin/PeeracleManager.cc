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
#include "VLCDataStream.h"

PeeracleManager::PeeracleManager(demux_t *demux) : _vlc(demux) {
}

PeeracleManager::~PeeracleManager() {
}

bool PeeracleManager::Init() {
  stream_t *metadataStream = this->_vlc->s;

  this->_metadataDataStream = new VLCDataStream(metadataStream);
  return true;
}

int PeeracleManager::Control(int i_query, va_list args) {
  switch (i_query) {
    case DEMUX_GET_POSITION:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_POSITION");
      break;
    case DEMUX_SET_POSITION:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_POSITION");
      break;
    case DEMUX_GET_LENGTH:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_LENGTH");
      break;
    case DEMUX_GET_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_TIME");
      break;
    case DEMUX_SET_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_TIME");
      break;
    case DEMUX_GET_TITLE_INFO:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_TITLE_INFO");
      break;
    case DEMUX_SET_TITLE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_TITLE");
      break;
    case DEMUX_SET_SEEKPOINT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_SEEKPOINT");
      break;
    case DEMUX_SET_GROUP:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_GROUP");
      break;
    case DEMUX_SET_ES:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_ES");
      break;
    case DEMUX_SET_NEXT_DEMUX_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_NEXT_DEMUX_TIME");
      break;
    case DEMUX_GET_FPS:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_FPS");
      break;
    case DEMUX_GET_META:
    {
      vlc_meta_t *p_meta =
        reinterpret_cast<vlc_meta_t*>(va_arg(args, vlc_meta_t*));
      vlc_meta_t *meta = vlc_meta_New();

      if (meta == NULL)
        return VLC_EGENERIC;

      vlc_meta_SetTitle(meta, "Metadata Title");
      vlc_meta_SetPublisher(meta, "Metadata Publisher");
      vlc_meta_SetCopyright(meta, "Metadata Copyright");
      vlc_meta_SetURL(meta, "Metadata URL");

      vlc_meta_Merge(p_meta, meta);
      vlc_meta_Delete(meta);
      return VLC_SUCCESS;
    }

    case DEMUX_HAS_UNSUPPORTED_META:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_HAS_UNSUPPORTED_META");
      break;
    case DEMUX_GET_ATTACHMENTS:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_ATTACHMENTS");
      break;
    case DEMUX_CAN_RECORD:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_RECORD");
      break;
    case DEMUX_SET_RECORD_STATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_RECORD_STATE");
      break;
    case DEMUX_GET_SIGNAL:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_SIGNAL");
      break;
    case DEMUX_CAN_PAUSE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_PAUSE = 0x1000");
      break;
    case DEMUX_SET_PAUSE_STATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_PAUSE_STATE");
      break;
    case DEMUX_GET_PTS_DELAY:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_PTS_DELAY");
      break;
    case DEMUX_CAN_CONTROL_PACE:
      *(va_arg (args, bool *)) = true;
      return VLC_SUCCESS;
    case DEMUX_CAN_CONTROL_RATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_CONTROL_RATE");
      break;
    case DEMUX_SET_RATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_RATE");
      break;
    case DEMUX_CAN_SEEK:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_SEEK");
      break;
    case DEMUX_IS_PLAYLIST:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_IS_PLAYLIST");
      break;
    case DEMUX_NAV_ACTIVATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_ACTIVATE");
      break;
    case DEMUX_NAV_UP:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_UP");
      break;
    case DEMUX_NAV_DOWN:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_DOWN");
      break;
    case DEMUX_NAV_LEFT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_LEFT");
      break;
    case DEMUX_NAV_RIGHT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_RIGHT");
      break;
    default:
      break;
  }
  return VLC_EGENERIC;
}

int PeeracleManager::Demux() {
  return VLC_DEMUXER_SUCCESS;
}
