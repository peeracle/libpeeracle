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

#include "samples/vlc-plugin/plugin.h"

/*****************************************************************************
 * Module descriptor
 *****************************************************************************/
static int Open(vlc_object_t *p_this);
static void Close(vlc_object_t *p_this);

static const uint8_t prcl_magic[] = {0x50, 0x52, 0x43, 0x4C};

vlc_module_begin()
  set_shortname("peeracle")
  set_description("peeracle metadata file access")
  set_capability("demux", 10)
  set_category(CAT_INPUT)
  set_subcategory(SUBCAT_INPUT_DEMUX)
  set_callbacks(Open, Close)
vlc_module_end()

/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
static int Demux(demux_t *p_demux);
static int Control(demux_t *p_demux, int i_query, va_list args);

/*****************************************************************************
 * Open:
 *****************************************************************************/
static int Open(vlc_object_t *p_obj) {
  demux_t *p_demux = reinterpret_cast<demux_t*>(p_obj);
  stream_t *stream = p_demux->s;
  demux_sys_t *p_sys;

  const uint8_t *peek;
  int peek_size;

  msg_Dbg(p_obj, "getting the four first bytes");
  peek_size = stream_Peek(stream, &peek, sizeof(prcl_magic));
  if (peek_size != sizeof(prcl_magic)) {
    msg_Dbg(p_obj, "header mismatch");
    return VLC_EGENERIC;
  }

  msg_Dbg(p_obj, "trying to malloc");
  p_sys = reinterpret_cast<demux_sys_t *>(malloc(sizeof(demux_sys_t)));
  if (unlikely(p_sys == NULL)) {
    msg_Dbg(p_obj, "out of memory");
    return VLC_ENOMEM;
  }

  p_demux->p_sys = p_sys;
  p_demux->pf_demux = Demux;
  p_demux->pf_control = Control;

  msg_Dbg(p_obj, "metadata file loaded successfully");
  return VLC_SUCCESS;
}
/*****************************************************************************
 * Close:
 *****************************************************************************/
static void Close(vlc_object_t *p_obj) {
  demux_t *p_demux = reinterpret_cast<demux_t*>(p_obj);
  demux_sys_t *p_sys = p_demux->p_sys;

  msg_Dbg(p_obj, "Close");
  free(p_sys);
}
/*****************************************************************************
 * Callbacks:
 *****************************************************************************/
static int Demux(demux_t *p_demux) {
  demux_sys_t *p_sys = p_demux->p_sys;

  // msg_Dbg(p_demux, "Demux");
  /*Stream::status status =
    p_sys->p_dashManager->demux(p_sys->i_nzpcr + DEMUX_INCREMENT);
  switch(status)
  {
    case Stream::status_eof:
      return VLC_DEMUXER_EOF;
    case Stream::status_buffering:
      break;
    case Stream::status_demuxed:
      p_sys->i_nzpcr += DEMUX_INCREMENT;
      int group = p_sys->p_dashManager->getGroup();
      es_out_Control(p_demux->out, ES_OUT_SET_GROUP_PCR, group, VLC_TS_0 + p_sys->i_nzpcr);
      break;
  }

  if( !p_sys->p_dashManager->updatePlaylist() )
    return VLC_DEMUXER_EOF;*/

  return VLC_DEMUXER_SUCCESS;
}

static int Control(demux_t *p_demux, int i_query, va_list args) {
  demux_sys_t *p_sys = p_demux->p_sys;

  switch (i_query) {
    case DEMUX_CAN_SEEK:
      /* *(va_arg (args, bool *)) = p_sys->p_dashManager->seekAble(); */
      msg_Dbg(p_demux, "Control: DEMUX_CAN_SEEK");
      break;

    case DEMUX_CAN_CONTROL_PACE:
      *(va_arg(args, bool *)) = true;
      msg_Dbg(p_demux, "Control: DEMUX_CAN_CONTROL_PACE");
      break;

    case DEMUX_CAN_PAUSE:
      /* *(va_arg (args, bool *)) = p_sys->p_mpd->isLive();*/
      msg_Dbg(p_demux, "Control: DEMUX_CAN_PAUSE");
      break;

    case DEMUX_GET_TIME:
      /* *(va_arg (args, int64_t *)) = p_sys->i_nzpcr;*/
      msg_Dbg(p_demux, "Control: DEMUX_GET_TIME");
      break;

    case DEMUX_GET_LENGTH:
      /* *(va_arg (args, int64_t *)) = p_sys->p_dashManager->getDuration();*/
      msg_Dbg(p_demux, "Control: DEMUX_GET_LENGTH");
      break;

    case DEMUX_GET_POSITION:
      /* if(!p_sys->p_dashManager->getDuration())
        return VLC_EGENERIC;

      *(va_arg (args, double *)) = (double) p_sys->i_nzpcr
                                   / p_sys->p_dashManager->getDuration();*/
      msg_Dbg(p_demux, "Control: DEMUX_GET_POSITION");
      break;

    case DEMUX_SET_POSITION:
    {
      /* int64_t time = p_sys->p_dashManager->getDuration() * va_arg(args, double);
      if(p_sys->p_mpd->isLive() ||
         !p_sys->p_dashManager->getDuration() ||
         !p_sys->p_dashManager->setPosition(time))
        return VLC_EGENERIC;
      p_sys->i_nzpcr = time;*/
      msg_Dbg(p_demux, "Control: DEMUX_SET_POSITION");
      break;
    }

    case DEMUX_SET_TIME:
    {
      /* int64_t time = va_arg(args, int64_t);
      if(p_sys->p_mpd->isLive() ||
         !p_sys->p_dashManager->setPosition(time))
        return VLC_EGENERIC;
      p_sys->i_nzpcr = time;*/
      msg_Dbg(p_demux, "Control: DEMUX_SET_TIME");
      break;
    }

    case DEMUX_GET_PTS_DELAY:
      /* *va_arg (args, int64_t *) = INT64_C(1000) *
      var_InheritInteger(p_demux, "network-caching");*/
      msg_Dbg(p_demux, "Control: DEMUX_GET_PTS_DELAY");
      break;

    case DEMUX_GET_META:
    {
      /* if(!p_sys->p_mpd->programInfo.Get())
        break;

      vlc_meta_t *p_meta = (vlc_meta_t *) va_arg (args, vlc_meta_t*);
      vlc_meta_t *meta = vlc_meta_New();
      if (meta == NULL)
        return VLC_EGENERIC;

      if(!p_sys->p_mpd->programInfo.Get()->getTitle().empty())
        vlc_meta_SetTitle(meta, p_sys->p_mpd->programInfo.Get()->getTitle().c_str());

      if(!p_sys->p_mpd->programInfo.Get()->getSource().empty())
        vlc_meta_SetPublisher(meta, p_sys->p_mpd->programInfo.Get()->getSource().c_str());

      if(!p_sys->p_mpd->programInfo.Get()->getCopyright().empty())
        vlc_meta_SetCopyright(meta, p_sys->p_mpd->programInfo.Get()->getCopyright().c_str());

      if(!p_sys->p_mpd->programInfo.Get()->getMoreInformationUrl().empty())
        vlc_meta_SetURL(meta, p_sys->p_mpd->programInfo.Get()->getMoreInformationUrl().c_str());

      vlc_meta_Merge(p_meta, meta);
      vlc_meta_Delete(meta);*/
      msg_Dbg(p_demux, "Control: DEMUX_GET_META");
      break;
    }

    default:
      return VLC_EGENERIC;
  }
  return VLC_SUCCESS;
}
