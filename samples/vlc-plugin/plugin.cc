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

#include <new>
#include <cstdint>
#include "samples/vlc-plugin/plugin.h"
#include "peeracle/Metadata/Metadata.h"
#include "samples/vlc-plugin/PeeracleManager.h"

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
    msg_Dbg(p_obj, "header size mismatch");
    return VLC_EGENERIC;
  }

  if (memcmp(peek, prcl_magic, sizeof(prcl_magic))) {
    msg_Dbg(p_obj, "header mismatch");
    return VLC_EGENERIC;
  }

  msg_Dbg(p_obj, "trying to malloc");
  p_sys = reinterpret_cast<demux_sys_t *>(malloc(sizeof(demux_sys_t)));
  if (unlikely(p_sys == NULL)) {
    msg_Dbg(p_obj, "out of memory");
    return VLC_ENOMEM;
  }

  msg_Dbg(p_obj, "trying to instantiate PeeracleManager");
  p_sys->p_peeracleManager = new(std::nothrow) PeeracleManager(stream);
  if (unlikely(p_sys->p_peeracleManager == NULL) ||
    !p_sys->p_peeracleManager->Init()) {
    msg_Dbg(p_obj, "out of memory");
    delete p_sys;
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
  delete p_sys->p_peeracleManager;
  free(p_sys);
}

/*****************************************************************************
 * Callbacks:
 *****************************************************************************/
static int Demux(demux_t *p_demux) {
  demux_sys_t *p_sys = p_demux->p_sys;
  return p_sys->p_peeracleManager->Demux();
}

static int Control(demux_t *p_demux, int i_query, va_list args) {
  demux_sys_t *p_sys = p_demux->p_sys;
  return p_sys->p_peeracleManager->Control(i_query, args);
}
