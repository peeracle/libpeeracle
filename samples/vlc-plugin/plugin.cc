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

int AccessOpen(vlc_object_t *p_this);
void AccessClose(vlc_object_t *p_this);
int StreamOpen(vlc_object_t *p_this);
void StreamClose(vlc_object_t *p_this);

static int Read(stream_t *s, void *p_read, unsigned int i_read);
static int Peek(stream_t *s, const uint8_t **pp_peek, unsigned int i_peek);
static int Control(stream_t *s, int i_query, va_list args);

struct stream_sys_t {
  char *psz_path;
  size_t i_len;
  size_t i_pos;
};

vlc_module_begin()
  set_shortname("peeracle")
  set_category(CAT_INPUT)

  set_subcategory(SUBCAT_INPUT_STREAM_FILTER)
  set_description("peeracle metadata files filter")
  set_capability("stream_filter", 15)
  set_callbacks(StreamOpen, StreamClose)

  add_submodule()
  set_subcategory(SUBCAT_INPUT_ACCESS)
  set_description("peeracle metadata file access")
  set_capability("access", 0)
  add_shortcut("peeracle", "prcl")
  set_callbacks(AccessOpen, AccessClose)
vlc_module_end()

int AccessOpen(vlc_object_t *p_this) {
  printf("peeracle_plugin AccessOpen\n");
  return VLC_EGENERIC;
}

void AccessClose(vlc_object_t *p_this) {
  printf("peeracle_plugin AccessClose\n");
}

static const uint8_t p_prcl_marker[] = {0x50, 0x52, 0x43, 0x4C};
static const int i_prcl_marker = 4;

int StreamOpen(vlc_object_t *p_this) {
  stream_t *s = reinterpret_cast<stream_t *>(p_this);
  stream_sys_t *p_sys;
  const uint8_t *p_peek;

  msg_Info(p_this, "peeracle_plugin StreamOpen\n");
  if (stream_Peek(s->p_source, &p_peek, i_prcl_marker) < i_prcl_marker) {
    printf("peeracle_plugin: Couldn't read 4 bytes.\n");
    return VLC_EGENERIC;
  }

  if (memcmp(p_peek, p_prcl_marker, i_prcl_marker)) {
    printf("peeracle_plugin: Header mismatch, %X%X%X%X\n", p_peek[0], p_peek[1],
           p_peek[2], p_peek[3]);
    return VLC_EGENERIC;
  }

  printf("peeracle_plugin: Correct metadata file, %X%X%X%X\n", p_peek[0],
         p_peek[1], p_peek[2], p_peek[3]);
  s->p_sys = p_sys = reinterpret_cast<stream_sys_t *>(calloc(1,
                                                             sizeof(*p_sys)));
  if (!p_sys) {
    return VLC_ENOMEM;
  }

  s->pf_read = Read;
  s->pf_peek = Peek;
  s->pf_control = Control;

  return VLC_SUCCESS;
}

void StreamClose(vlc_object_t *p_this) {
  printf("peeracle_plugin StreamClose\n");
}

static int Read(stream_t *s, void *p_read, unsigned int i_read) {
  stream_sys_t *p_sys = s->p_sys;

  printf("peeracle_plugin Read %u\n", i_read);
  /* Fill the buffer */
  /* if (Fill(s))
    return -1; */

  /* Read the buffer */
  /* unsigned i_len = __MIN(i_read, p_sys->i_len - p_sys->i_pos);
  if (p_read)
    memcpy(p_read, p_sys->psz_xspf + p_sys->i_pos, i_len);
  p_sys->i_pos += i_len; */

  /* return i_len; */
  return -1;
}

/** *************************************************************************
 * Peek
 ****************************************************************************/
static int Peek(stream_t *s, const uint8_t **pp_peek, unsigned int i_peek) {
  stream_sys_t *p_sys = s->p_sys;

  printf("peeracle_plugin Peek %u\n", i_peek);
  /* Fill the buffer */
  /* if (Fill(s))
    return -1; */

  /* Point to the buffer */
  /* int i_len = __MIN(i_peek, p_sys->i_len - p_sys->i_pos); */
  /* *pp_peek = (uint8_t *) p_sys->psz_xspf + p_sys->i_pos; */

  /* return i_len; */
  return -1;
}

/** *************************************************************************
 * Control
 ****************************************************************************/

static int Control(stream_t *s, int i_query, va_list args) {
  stream_sys_t *p_sys = s->p_sys;

  switch (i_query) {
    case STREAM_SET_POSITION: {
      uint64_t i_position = va_arg(args, uint64_t);
      printf("peeracle_plugin STREAM_SET_POSITION %lu\n", i_position);
      if (i_position >= p_sys->i_len) {
        return VLC_EGENERIC;
      } else {
        p_sys->i_pos = (size_t) i_position;
        return VLC_SUCCESS;
      }
    }

    case STREAM_GET_POSITION: {
      uint64_t *pi_position = va_arg(args, uint64_t*);
      printf("peeracle_plugin STREAM_GET_POSITION\n");
      *pi_position = p_sys->i_pos;
      return VLC_SUCCESS;
    }

    case STREAM_GET_SIZE: {
      uint64_t *pi_size = va_arg(args, uint64_t*);
      printf("peeracle_plugin STREAM_GET_SIZE\n");
      *pi_size = p_sys->i_len;
      return VLC_SUCCESS;
    }

    case STREAM_GET_CONTENT_TYPE:
      return VLC_EGENERIC;

    case STREAM_UPDATE_SIZE:
    case STREAM_CAN_SEEK:
    case STREAM_CAN_FASTSEEK:
    case STREAM_SET_RECORD_STATE:
      return stream_vaControl(s->p_source, i_query, args);

    default:
      return VLC_EGENERIC;
  }
}
