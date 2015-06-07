/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef _REENTRANT
# define _REENTRANT
#endif


#if defined(_WIN32) && !defined(_WIN32_WINNT)

# define _WIN32_WINNT 0x0502 /* Windows XP SP2 */

#endif

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 to allow running VLC as root (uid 0). */
/* #undef ALLOW_RUN_AS_ROOT */

/* Maximum supported data alignment */
#define ATTRIBUTE_ALIGNED_MAX 64

/* Define to 1 if 3D Now! inline assembly is available. */
#define CAN_COMPILE_3DNOW 1

/* Define to 1 if AltiVec inline assembly is available. */
/* #undef CAN_COMPILE_ALTIVEC */

/* Define to 1 if C AltiVec extensions are available. */
/* #undef CAN_COMPILE_C_ALTIVEC */

/* Define to 1 inline MMX assembly is available. */
#define CAN_COMPILE_MMX 1

/* Define to 1 if MMX EXT inline assembly is available. */
#define CAN_COMPILE_MMXEXT 1

/* Define to 1 if SSE inline assembly is available. */
#define CAN_COMPILE_SSE 1

/* Define to 1 if SSE2 inline assembly is available. */
#define CAN_COMPILE_SSE2 1

/* Define to 1 if SSE3 inline assembly is available. */
#define CAN_COMPILE_SSE3 1

/* Define to 1 if SSE4A inline assembly is available. */
#define CAN_COMPILE_SSE4A 1

/* Define to 1 if SSE4_1 inline assembly is available. */
#define CAN_COMPILE_SSE4_1 1

/* Define to 1 if SSE4_2 inline assembly is available. */
#define CAN_COMPILE_SSE4_2 1

/* Define to 1 if SSSE3 inline assembly is available. */
#define CAN_COMPILE_SSSE3 1

/* The ./configure command line */
#define CONFIGURE_LINE "../extras/package/win32/../../../configure  '--enable-update-check' '--enable-lua' '--enable-faad' '--enable-flac' '--enable-theora' '--enable-twolame' '--enable-quicktime' '--enable-avcodec' '--enable-merge-ffmpeg' '--enable-dca' '--enable-mpc' '--enable-libass' '--enable-x264' '--enable-schroedinger' '--enable-realrtsp' '--enable-live555' '--enable-dvdread' '--enable-shout' '--enable-goom' '--enable-caca' '--enable-qt' '--enable-skins2' '--enable-sse' '--enable-mmx' '--enable-libcddb' '--enable-zvbi' '--enable-nls' '--host=i686-w64-mingw32' '--disable-nls' '--enable-static' '--disable-shared' '--disable-archive' '--disable-live555' '--disable-dc1394' '--disable-dv1394' '--disable-linsys' '--disable-dvdread' '--disable-dvdnav' '--disable-bluray' '--disable-opencv' '--disable-smbclient' '--disable-dsm' '--disable-sftp' '--disable-v4l2' '--disable-decklink' '--disable-gnomevfs' '--disable-vcdx' '--disable-vcd' '--disable-libcddb' '--disable-screen' '--disable-vnc' '--disable-freerdp' '--disable-realrtsp' '--disable-macosx-eyetv' '--disable-macosx-qtkit' '--disable-macosx-avfoundation' '--disable-asdcp' '--disable-dvbpsi' '--disable-gme' '--disable-sid' '--disable-ogg' '--disable-shout' '--disable-mkv' '--disable-mod' '--disable-mpc' '--disable-wma-fixed' '--disable-shine' '--disable-omxil' '--disable-omxil-vout' '--disable-rpi-omxil' '--disable-crystalhd' '--disable-mad' '--disable-mpg123' '--disable-merge-ffmpeg' '--disable-gst-decode' '--disable-avcodec' '--disable-libva' '--disable-dxva2' '--disable-vda' '--disable-avformat' '--disable-swscale' '--disable-postproc' '--disable-faad' '--disable-vpx' '--disable-twolame' '--disable-fdkaac' '--disable-quicktime' '--disable-a52' '--disable-dca' '--disable-flac' '--disable-libmpeg2' '--disable-vorbis' '--disable-tremor' '--disable-speex' '--disable-opus' '--disable-theora' '--disable-daala' '--disable-schroedinger' '--disable-png' '--disable-jpeg' '--disable-bpg' '--disable-x262' '--disable-x265' '--disable-x26410b' '--disable-x264' '--disable-mfx' '--disable-fluidsynth' '--disable-zvbi' '--disable-telx' '--disable-libass' '--disable-aribsub' '--disable-aribb25' '--disable-kate' '--disable-tiger' '--disable-gles2' '--disable-gles1' '--without-x' '--disable-xcb' '--disable-xvideo' '--disable-vdpau' '--disable-wayland' '--disable-sdl' '--disable-sdl-image' '--disable-freetype' '--disable-fribidi' '--disable-harfbuzz' '--disable-fontconfig' '--disable-macosx-quartztext' '--disable-svg' '--disable-svgdec' '--disable-android-surface' '--disable-directx' '--disable-directfb' '--disable-aa' '--disable-caca' '--disable-kva' '--disable-mmal' '--disable-pulse' '--disable-alsa' '--disable-oss' '-disable-sndio' '--disable-wasapi' '--disable-audioqueue' '--disable-jack' '--disable-opensles' '--disable-samplerate' '--disable-kai' '--disable-chromaprint' '--disable-chromecast' '--disable-qt' '--disable-skins2' '--disable-macosx' '--disable-minimal-macosx' '--disable-ncurses' '--disable-macosx-dialog-provider' '--disable-lirc' '--disable-goom' '--disable-projectm' '--disable-vsxu' '--disable-atmo' '--disable-bonjour' '--disable-udev' '--disable-mtp' '--disable-upnp' '--disable-libxml2' '--disable-libgcrypt' '--disable-gnutls' '--disable-taglib' '--disable-update-check' '--disable-growl' '--disable-notify' '--disable-vlc' '--disable-macosx-vlc-app' 'host_alias=i686-w64-mingw32'"

/* Copyright string */
#define COPYRIGHT_MESSAGE "Copyright © 1996-2015 the VideoLAN team"

/* The copyright years */
#define COPYRIGHT_YEARS "1996-2015"

/* Default font family */
/* #undef DEFAULT_FAMILY */

/* Default font */
/* #undef DEFAULT_FONT_FILE */

/* Default monospace font family */
/* #undef DEFAULT_MONOSPACE_FAMILY */

/* Default monospace font */
/* #undef DEFAULT_MONOSPACE_FONT_FILE */

/* Binary specific version */
/* #undef DISTRO_VERSION */

/* Define if you want the addons manager modules */
#define ENABLE_ADDONMANAGERMODULES 1

/* Define if you want the HTTP daemon support */
#define ENABLE_HTTPD 1

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* Define to 1 for stream output support. */
#define ENABLE_SOUT 1

/* Define if you want the VideoLAN manager support */
#define ENABLE_VLM 1

/* Define to 1 if you have the <a52dec/a52.h> header file. */
/* #undef HAVE_A52DEC_A52_H */

/* Define to 1 if you have the `accept4' function. */
/* #undef HAVE_ACCEPT4 */

/* Define to 1 if you have the <altivec.h> header file. */
/* #undef HAVE_ALTIVEC_H */

/* Define to 1 if you have the <ApplicationServices/ApplicationServices.h>
   header file. */
/* #undef HAVE_APPLICATIONSERVICES_APPLICATIONSERVICES_H */

/* Define if libaribb24 is available. */
/* #undef HAVE_ARIBB24 */

/* Define to 1 if you have the <arpa/inet.h> header file. */
/* #undef HAVE_ARPA_INET_H */

/* Define to 1 if you have asprintf function */
#define HAVE_ASPRINTF 1

/* Define to 1 if you have the `atof' function. */
#define HAVE_ATOF 1

/* Define to 1 if you have the `atoll' function. */
#define HAVE_ATOLL 1

/* Support for __attribute__((packed)) for structs */
#define HAVE_ATTRIBUTE_PACKED 1

/* Define to 1 if you have the `av_vda_alloc_context' function. */
/* #undef HAVE_AV_VDA_ALLOC_CONTEXT */

/* Define to 1 if you have the `backtrace' function. */
/* #undef HAVE_BACKTRACE */

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* define if the compiler supports basic C++11 syntax */
#define HAVE_CXX11 1

/* Define to 1 if you have the <d2d1.h> header file. */
/* #undef HAVE_D2D1_H */

/* Define to 1 if you have the <d3d11.h> header file. */
/* #undef HAVE_D3D11_H */

/* Define to 1 if you have the <d3d9.h> header file. */
/* #undef HAVE_D3D9_H */

/* Define to 1 if you have the `daemon' function. */
/* #undef HAVE_DAEMON */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
/* #undef HAVE_DCGETTEXT */

/* Define to 1 if you have the <ddraw.h> header file. */
/* #undef HAVE_DDRAW_H */

/* Define to 1 if you have the <DeckLinkAPIDispatch.cpp> header file. */
/* #undef HAVE_DECKLINKAPIDISPATCH_CPP */

/* Define to 1 if you have the declaration of `nanosleep', and to 0 if you
   don't. */
#define HAVE_DECL_NANOSLEEP 1

/* Define to 1 if you have the `dirfd' function. */
/* #undef HAVE_DIRFD */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the <dxva2api.h> header file. */
/* #undef HAVE_DXVA2API_H */

/* Define to 1 if you have the <ebml/EbmlVersion.h> header file. */
/* #undef HAVE_EBML_EBMLVERSION_H */

/* Define to 1 if you have the `eventfd' function. */
/* #undef HAVE_EVENTFD */

/* Define to 1 if you have the <execinfo.h> header file. */
/* #undef HAVE_EXECINFO_H */

/* Define to 1 if you have the `fcntl' function. */
/* #undef HAVE_FCNTL */

/* Define to 1 if you have the `fdatasync' function. */
/* #undef HAVE_FDATASYNC */

/* Define to 1 if you have the `fdopendir' function. */
/* #undef HAVE_FDOPENDIR */

/* Define to 1 if you have the `flockfile' function. */
/* #undef HAVE_FLOCKFILE */

/* Define to 1 if you have the <fontconfig/fontconfig.h> header file. */
/* #undef HAVE_FONTCONFIG_FONTCONFIG_H */

/* Define to 1 if you have the `fork' function. */
/* #undef HAVE_FORK */

/* Define to 1 if you have the `fstatvfs' function. */
/* #undef HAVE_FSTATVFS */

/* Define to 1 if you have the `fsync' function. */
/* #undef HAVE_FSYNC */

/* Define to 1 if you have the `getdelim' function. */
/* #undef HAVE_GETDELIM */

/* Define to 1 if you have the `getenv' function. */
#define HAVE_GETENV 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getpid' function. */
#define HAVE_GETPID 1

/* Define to 1 if you have the `getpwuid_r' function. */
/* #undef HAVE_GETPWUID_R */

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define to 1 if you have the <GL/wglew.h> header file. */
/* #undef HAVE_GL_WGLEW_H */

/* Define to 1 if you have gmtime_r function */
/* #undef HAVE_GMTIME_R */

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define to 1 if you have GNU libidn. */
/* #undef HAVE_IDN */

/* Define to 1 if you have the `if_nameindex' function. */
/* #undef HAVE_IF_NAMEINDEX */

/* Define to 1 if you have the `if_nametoindex' function. */
/* #undef HAVE_IF_NAMETOINDEX */

/* Define to 1 if you have inet_pton function */
/* #undef HAVE_INET_PTON */

/* Define to 1 if you have the <interface/mmal/mmal.h> header file. */
/* #undef HAVE_INTERFACE_MMAL_MMAL_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* For FreeBSD VCD support */
/* #undef HAVE_IOC_TOC_HEADER_IN_SYS_CDIO_H */

/* Define to 1 if you have the `isatty' function. */
#define HAVE_ISATTY 1

/* Define to 1 if you have the <jpeglib.h> header file. */
/* #undef HAVE_JPEGLIB_H */

/* Define to 1 if you have the <kai.h> header file. */
/* #undef HAVE_KAI_H */

/* Define to 1 if you have the <kva.h> header file. */
/* #undef HAVE_KVA_H */

/* Define to 1 if you have the <lauxlib.h> header file. */
/* #undef HAVE_LAUXLIB_H */

/* Define to 1 if you have the <libavcodec/avcodec.h> header file. */
/* #undef HAVE_LIBAVCODEC_AVCODEC_H */

/* Define to 1 if you have the <libavcodec/dxva2.h> header file. */
/* #undef HAVE_LIBAVCODEC_DXVA2_H */

/* Define to 1 if you have the <libavcodec/vaapi.h> header file. */
/* #undef HAVE_LIBAVCODEC_VAAPI_H */

/* Define to 1 if you have the <libavcodec/vda.h> header file. */
/* #undef HAVE_LIBAVCODEC_VDA_H */

/* Define to 1 if you have the <libavformat/avformat.h> header file. */
/* #undef HAVE_LIBAVFORMAT_AVFORMAT_H */

/* Define to 1 if you have the <libavformat/avio.h> header file. */
/* #undef HAVE_LIBAVFORMAT_AVIO_H */

/* Define to 1 if you have the <libavutil/avutil.h> header file. */
/* #undef HAVE_LIBAVUTIL_AVUTIL_H */

/* Define to 1 if you have the <libbpg.h> header file. */
/* #undef HAVE_LIBBPG_H */

/* Define this if you have libcddb installed */
/* #undef HAVE_LIBCDDB */

/* Define to 1 if you have the <libcrystalhd/bc_drv_if.h> header file. */
/* #undef HAVE_LIBCRYSTALHD_BC_DRV_IF_H */

/* Define to 1 if you have the <libcrystalhd/bc_dts_defs.h> header file. */
/* #undef HAVE_LIBCRYSTALHD_BC_DTS_DEFS_H */

/* Define to 1 if you have the `mingw32' library (-lmingw32). */
#define HAVE_LIBMINGW32 1

/* Define to 1 if you have the <libswscale/swscale.h> header file. */
/* #undef HAVE_LIBSWSCALE_SWSCALE_H */

/* Define to 1 if you have the <libtar.h> header file. */
/* #undef HAVE_LIBTAR_H */

/* Define to 1 if you have the libvorbis */
#define HAVE_LIBVORBIS 1

/* Define to 1 if you have the <linux/dccp.h> header file. */
/* #undef HAVE_LINUX_DCCP_H */

/* Define to 1 if you have the <linux/magic.h> header file. */
/* #undef HAVE_LINUX_MAGIC_H */

/* Define to 1 if you have the <linux/videodev2.h> header file. */
/* #undef HAVE_LINUX_VIDEODEV2_H */

/* Define to 1 if you have the `lldiv' function. */
#define HAVE_LLDIV 1

/* Define to 1 if you have localtime_r function */
/* #undef HAVE_LOCALTIME_R */

/* Define to 1 if you have the lrintf function */
#define HAVE_LRINTF 1

/* Define to 1 if you have the `lstat' function. */
/* #undef HAVE_LSTAT */

/* Define to 1 if you have the <lualib.h> header file. */
/* #undef HAVE_LUALIB_H */

/* Define to 1 if you have the <lua.h> header file. */
/* #undef HAVE_LUA_H */

/* Define to 1 if you have the <mad.h> header file. */
/* #undef HAVE_MAD_H */

/* Define to 1 if you have the <matroska/KaxAttachments.h> header file. */
/* #undef HAVE_MATROSKA_KAXATTACHMENTS_H */

/* Define to 1 if you have the <matroska/KaxVersion.h> header file. */
/* #undef HAVE_MATROSKA_KAXVERSION_H */

/* Define to 1 if you have the `memalign' function. */
/* #undef HAVE_MEMALIGN */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mmap' function. */
/* #undef HAVE_MMAP */

/* Define to 1 if MMX intrinsics are available. */
#define HAVE_MMX_INTRINSICS 1

/* Define to 1 if you have the <mntent.h> header file. */
/* #undef HAVE_MNTENT_H */

/* Define to 1 if you have the <mpcdec/mpcdec.h> header file. */
/* #undef HAVE_MPCDEC_MPCDEC_H */

/* Define to 1 if you have the <mpc/mpcdec.h> header file. */
/* #undef HAVE_MPC_MPCDEC_H */

/* Define to 1 if you have the NANF function */
#define HAVE_NANF 1

/* Define to 1 if you have the <neaacdec.h> header file. */
/* #undef HAVE_NEAACDEC_H */

/* Define to 1 if you have the <netinet/udplite.h> header file. */
/* #undef HAVE_NETINET_UDPLITE_H */

/* Define to 1 if you have the <net/if.h> header file. */
/* #undef HAVE_NET_IF_H */

/* Define to 1 if you have the `nrand48' function. */
/* #undef HAVE_NRAND48 */

/* Define to 1 if you have the `openat' function. */
/* #undef HAVE_OPENAT */

/* Define to 1 if you have the `open_memstream' function. */
/* #undef HAVE_OPEN_MEMSTREAM */

/* Define to 1 if you have the `pipe2' function. */
/* #undef HAVE_PIPE2 */

/* Define to 1 if you have the <png.h> header file. */
/* #undef HAVE_PNG_H */

/* Define to 1 if you have the `poll' function. */
/* #undef HAVE_POLL */

/* Define to 1 if you have the `posix_fadvise' function. */
/* #undef HAVE_POSIX_FADVISE */

/* Define to 1 if you have the `posix_madvise' function. */
/* #undef HAVE_POSIX_MADVISE */

/* Define to 1 if you have the `posix_memalign' function. */
/* #undef HAVE_POSIX_MEMALIGN */

/* Define to 1 if you have the <postproc/postprocess.h> header file. */
/* #undef HAVE_POSTPROC_POSTPROCESS_H */

/* Define to 1 if you have the `pread' function. */
/* #undef HAVE_PREAD */

/* Define to 1 if using libprojectM 2.x */
/* #undef HAVE_PROJECTM2 */

/* Define to 1 if you have the `pthread_condattr_setclock' function. */
#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1

/* Define to 1 if you have the `pthread_cond_timedwait_monotonic_np' function.
   */
/* #undef HAVE_PTHREAD_COND_TIMEDWAIT_MONOTONIC_NP */

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if you have the <QuickTime/QuickTime.h> header file. */
/* #undef HAVE_QUICKTIME_QUICKTIME_H */

/* Define to 1 if you have the `rewind' function. */
#define HAVE_REWIND 1

/* Define to 1 if you have the `sched_getaffinity' function. */
/* #undef HAVE_SCHED_GETAFFINITY */

/* For NetBSD VCD support */
/* #undef HAVE_SCSIREQ_IN_SYS_SCSIIO_H */

/* Define to 1 if you have the <search.h> header file. */
#define HAVE_SEARCH_H 1

/* Define to 1 if you have the `setenv' function. */
/* #undef HAVE_SETENV */

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <SLES/OpenSLES.h> header file. */
/* #undef HAVE_SLES_OPENSLES_H */

/* Define to 1 if you have the <soundcard.h> header file. */
/* #undef HAVE_SOUNDCARD_H */

/* Define to 1 if SSE2 intrinsics are available. */
#define HAVE_SSE2_INTRINSICS 1

/* Define to 1 if <assert.h> defines static_assert. */
#define HAVE_STATIC_ASSERT 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strcasestr' function. */
/* #undef HAVE_STRCASESTR */

/* Define to 1 if you have the `strcoll' function and it is properly defined.
   */
#define HAVE_STRCOLL 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `stricmp' function. */
#define HAVE_STRICMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcpy' function. */
/* #undef HAVE_STRLCPY */

/* Define to 1 if you have the `strndup' function. */
/* #undef HAVE_STRNDUP */

/* Define to 1 if you have the `strnicmp' function. */
#define HAVE_STRNICMP 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strptime' function. */
/* #undef HAVE_STRPTIME */

/* Define to 1 if you have the `strsep' function. */
/* #undef HAVE_STRSEP */

/* Define to 1 if you have the `strtof' function. */
#define HAVE_STRTOF 1

/* Define to 1 if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define to 1 if you have the `strtoll' function. */
#define HAVE_STRTOLL 1

/* Define to 1 if the system has the type `struct pollfd'. */
/* #undef HAVE_STRUCT_POLLFD */

/* Define to 1 if you have the `strverscmp' function. */
/* #undef HAVE_STRVERSCMP */

/* Define to 1 if you have the `swab' function. */
#define HAVE_SWAB 1

/* Define to 1 if you have the <sys/eventfd.h> header file. */
/* #undef HAVE_SYS_EVENTFD_H */

/* Define to 1 if you have the <sys/mount.h> header file. */
/* #undef HAVE_SYS_MOUNT_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/shm.h> header file. */
/* #undef HAVE_SYS_SHM_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
/* #undef HAVE_SYS_SOCKET_H */

/* Define to 1 if you have the <sys/soundcard.h> header file. */
/* #undef HAVE_SYS_SOUNDCARD_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/videoio.h> header file. */
/* #undef HAVE_SYS_VIDEOIO_H */

/* Define to 1 if you have the `tdestroy' function. */
/* #undef HAVE_TDESTROY */

/* Define if libtiger is available. */
/* #undef HAVE_TIGER */

/* Define to 1 if you have the <tremor/ivorbiscodec.h> header file. */
/* #undef HAVE_TREMOR_IVORBISCODEC_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <unzip.h> header file. */
/* #undef HAVE_UNZIP_H */

/* Define to 1 if you have the `uselocale' function. */
/* #undef HAVE_USELOCALE */

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
/* #undef HAVE_VALGRIND_VALGRIND_H */

/* Define to 1 if you have vasprintf function */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the <VideoDecodeAcceleration/VDADecoder.h> header
   file. */
/* #undef HAVE_VIDEODECODEACCELERATION_VDADECODER_H */

/* Define to 1 if you have the `vmsplice' function. */
/* #undef HAVE_VMSPLICE */

/* Define to 1 if you have the <X11/Xlib.h> header file. */
/* #undef HAVE_X11_XLIB_H */

/* Define to 1 if you have the <xlocale.h> header file. */
/* #undef HAVE_XLOCALE_H */

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if you have the `_lock_file' function. */
/* #undef HAVE__LOCK_FILE */

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Dynamic object extension */
#define LIBEXT ".dll"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if debug code should NOT be compiled */
#define NDEBUG 1

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define if <sys/param.h> defines ntohl. */
/* #undef NTOHL_IN_SYS_PARAM_H */

/* Define if you want to optimize memory usage over performance */
/* #undef OPTIMIZE_MEMORY */

/* Name of package */
#define PACKAGE "vlc"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "vlc"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "vlc 3.0.0-git"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "vlc"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.0.0-git"

/* version development string */
#define PACKAGE_VERSION_DEV "git"

/* version extra number */
#define PACKAGE_VERSION_EXTRA 0

/* version major number */
#define PACKAGE_VERSION_MAJOR 3

/* version minor number */
#define PACKAGE_VERSION_MINOR 0

/* version revision number */
#define PACKAGE_VERSION_REVISION 0

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 for Unicode (Wide Chars) APIs. */
#define UNICODE 1

/* Define if you want to use the VLC update mechanism */
/* #undef UPDATE_CHECK */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "3.0.0-git"

/* Simple version string */
#define VERSION_MESSAGE "3.0.0-git Vetinari"

/* compiler */
#define VLC_COMPILER "gcc version 4.8.3 (GCC)"

/* user who ran configure */
#define VLC_COMPILE_BY "vm"

/* host which ran configure */
#define VLC_COMPILE_HOST "vm-PC"

/* Define to 1 if you want to build for Windows Store apps */
#define VLC_WINSTORE_APP 0

/* Define to limit the scope of <windows.h>. */
#ifndef _MSC_VER
# define WIN32_LEAN_AND_MEAN /**/
#endif

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if the X Window System is missing or not being used. */
#define X_DISPLAY_MISSING 1

/* Define if the zvbi module is built */
/* #undef ZVBI_COMPILED */

/* ISO C, POSIX, and 4.3BSD things. */
#define _BSD_SOURCE 1

/* Define to 64 for large files support. */
#define _FILE_OFFSET_BITS 64

/* Define to 2 to get glibc warnings. */
#define _FORTIFY_SOURCE 2

/* Extensions to ISO C99 from ISO C11. */
#define _ISOC11_SOURCE 1

/* Extensions to ISO C89 from ISO C99. */
#define _ISOC99_SOURCE 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* IEEE Std 1003.1. */
#define _POSIX_C_SOURCE 200809L

/* IEEE Std 1003.1. */
#define _POSIX_SOURCE 1

/* ISO C, POSIX, and SVID things. */
#define _SVID_SOURCE 1

/* Same as _REENTANT for some other OSes. */
#define _THREAD_SAFE /**/

/* Define to 1 for Unicode (Wide Chars) APIs. */
#define _UNICODE 1

/* Define to '0x0600' for IE 6.0 (and shell) APIs. */
#define _WIN32_IE 0x0600

/* POSIX and XPG 7th edition */
#define _XOPEN_SOURCE 700

/* XPG things and X/Open Unix extensions. */
#define _XOPEN_SOURCE_EXTENDED 1

/* Define within the LibVLC source code tree. */
/* #undef __LIBVLC__ */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Alias fdatasync() to fsync() if missing. */
#define fdatasync fsync

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `sockaddr' if <sys/socket.h> does not define. */
/* #undef sockaddr_storage */

/* Define to `int' if <sys/socket.h> does not define. */
/* #undef socklen_t */

/* Define to `sa_family' if <sys/socket.h> does not define. */
/* #undef ss_family */

#ifdef _MSC_VER
/* Define to `int' if <stddef.h> does not define. */
#define ssize_t intptr_t

#define __func__ __FUNCTION__ 
#endif

#ifndef __FAST_MATH__
# ifndef _MSC_VER
#  pragma STDC FENV_ACCESS OFF
#  pragma STDC FP_CONTRACT ON
# else
#  pragma fenv_access(off)
#  pragma fp_contract(on)
# endif
#endif

#ifdef _MSC_VER
int poll(struct pollfd *fds, unsigned nfds, int timeout);
int strcasecmp (const char *s1, const char *s2);
#endif
