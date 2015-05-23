{
  'includes': [
    '../build/common.gypi',
  ],
  'variables': {
    'target_arch%': 'x64',
    'configuration%': 'Release',
    'peeracle_dir': '<(DEPTH)/peeracle',
    'webrtc_dir': '<!(pwd)/../third_party/webrtc',
  },
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'sources': [
        'lib/createanswerobserver.cc',
        'lib/createofferobserver.cc',
        'lib/createsessiondescriptionobserver.cc',
        'lib/manager.cc',
        'lib/peer.cc',
        'lib/setanswerobserver.cc',
        'lib/setlocalofferobserver.cc',
        'lib/setremoteofferobserver.cc',
        'lib/setsessiondescriptionobserver.cc',
      ],
      'include_dirs': [
        '<(webrtc_dir)',
        '<(webrtc_dir)/third_party',
      ],
      'conditions': [
        ['OS == "win"', {
          'defines': [
            'WEBRTC_WIN',
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': 0,
            },
          },
          'link_settings': {
            'libraries': [
              '<!@(C:/MinGW/msys/1.0/bin/find <(webrtc_dir)/out/Release -name *.lib -type f)',
              '-ladvapi32.lib',
              '-lamstrmid.lib',
              '-ldmoguids.lib',
              '-lmsdmo.lib',
              '-lole32.lib',
              '-lsecur32.lib',
              '-lshell32.lib',
              '-lstrmiids.lib',
              '-lwmcodecdspuuid.lib',
            ],
          },
        }, {
          'defines': [
            'WEBRTC_POSIX',
          ],
        }],
        ['OS == "linux"', {
          'defines': [
            'WEBRTC_LINUX'
          ],
          'link_settings': {
            'libraries': [
              '-Wl,--start-group',
              '<!@(find <(webrtc_dir)/out/Release -name *.a -type f)',
              '-lpthread',
              '-ldl',
              '-lnss3',
              '-lnssutil3',
              '-lplc4',
              '-lnspr4',
              '-lX11',
              '-Wl,--end-group'
            ],
          },
        }],
        ['OS == "mac"', {
          'link_settings': {
            'libraries': [
              '-framework AVFoundation',
              '-framework Cocoa',
              '-framework Foundation',
              '-framework IOKit',
              '-framework Security',
              '-framework SystemConfiguration',
              '-weak_framework AVFoundation',
              '-framework CoreAudio',
              '-framework CoreVideo',
              '-framework OpenGL',
              '-framework QTKit',
              '-framework CFNetwork',
              '<(webrtc_dir)/out/Release/libapprtc_signaling.a',
              '<(webrtc_dir)/out/Release/libjingle_peerconnection.a',
              '<(webrtc_dir)/out/Release/librtc_base.a',
              '<(webrtc_dir)/out/Release/libwebrtc_common.a',
              '<(webrtc_dir)/out/Release/librtc_base_approved.a',
              '<(webrtc_dir)/out/Release/libjsoncpp.a',
              '<(webrtc_dir)/out/Release/libboringssl.a',
              '<(webrtc_dir)/out/Release/libexpat.a',
              '<(webrtc_dir)/out/Release/libjingle_media.a',
              '<(webrtc_dir)/out/Release/libvideo_render_module.a',
              '<(webrtc_dir)/out/Release/libwebrtc_utility.a',
              '<(webrtc_dir)/out/Release/libaudio_coding_module.a',
              '<(webrtc_dir)/out/Release/libCNG.a',
              '<(webrtc_dir)/out/Release/libcommon_audio.a',
              '<(webrtc_dir)/out/Release/libsystem_wrappers.a',
              '<(webrtc_dir)/out/Release/libopenmax_dl.a',
              '<(webrtc_dir)/out/Release/libcommon_audio_sse2.a',
              '<(webrtc_dir)/out/Release/libaudio_encoder_interface.a',
              '<(webrtc_dir)/out/Release/libG711.a',
              '<(webrtc_dir)/out/Release/libG722.a',
              '<(webrtc_dir)/out/Release/libiLBC.a',
              '<(webrtc_dir)/out/Release/libiSAC.a',
              '<(webrtc_dir)/out/Release/libaudio_decoder_interface.a',
              '<(webrtc_dir)/out/Release/libiSACFix.a',
              '<(webrtc_dir)/out/Release/libPCM16B.a',
              '<(webrtc_dir)/out/Release/libred.a',
              '<(webrtc_dir)/out/Release/libwebrtc_opus.a',
              '<(webrtc_dir)/out/Release/libopus.a',
              '<(webrtc_dir)/out/Release/libneteq.a',
              '<(webrtc_dir)/out/Release/libmedia_file.a',
              '<(webrtc_dir)/out/Release/libcommon_video.a',
              '<(webrtc_dir)/out/Release/libyuv.a',
              '<(webrtc_dir)/out/Release/libjpeg_turbo.a',
              '<(webrtc_dir)/out/Release/libwebrtc.a',
              '<(webrtc_dir)/out/Release/libvideo_engine_core.a',
              '<(webrtc_dir)/out/Release/librtp_rtcp.a',
              '<(webrtc_dir)/out/Release/libpaced_sender.a',
              '<(webrtc_dir)/out/Release/libremote_bitrate_estimator.a',
              '<(webrtc_dir)/out/Release/libbitrate_controller.a',
              '<(webrtc_dir)/out/Release/libvideo_capture_module.a',
              '<(webrtc_dir)/out/Release/libwebrtc_video_coding.a',
              '<(webrtc_dir)/out/Release/libwebrtc_i420.a',
              '<(webrtc_dir)/out/Release/libvideo_coding_utility.a',
              '<(webrtc_dir)/out/Release/libwebrtc_vp8.a',
              '<(webrtc_dir)/out/Release/libvpx.a',
              '<(webrtc_dir)/out/Release/libvpx_intrinsics_mmx.a',
              '<(webrtc_dir)/out/Release/libvpx_intrinsics_sse2.a',
              '<(webrtc_dir)/out/Release/libvpx_intrinsics_ssse3.a',
              '<(webrtc_dir)/out/Release/libvpx_intrinsics_sse4_1.a',
              '<(webrtc_dir)/out/Release/libvpx_intrinsics_avx2.a',
              '<(webrtc_dir)/out/Release/libwebrtc_vp9.a',
              '<(webrtc_dir)/out/Release/libvideo_processing.a',
              '<(webrtc_dir)/out/Release/libvideo_processing_sse2.a',
              '<(webrtc_dir)/out/Release/libvoice_engine.a',
              '<(webrtc_dir)/out/Release/libaudio_conference_mixer.a',
              '<(webrtc_dir)/out/Release/libaudio_processing.a',
              '<(webrtc_dir)/out/Release/libaudioproc_debug_proto.a',
              '<(webrtc_dir)/out/Release/libprotobuf_lite.a',
              '<(webrtc_dir)/out/Release/libaudio_processing_sse2.a',
              '<(webrtc_dir)/out/Release/libaudio_device.a',
              '<(webrtc_dir)/out/Release/librtc_sound.a',
              '<(webrtc_dir)/out/Release/libfield_trial_default.a',
              '<(webrtc_dir)/out/Release/libmetrics_default.a',
              '<(webrtc_dir)/out/Release/librtc_xmllite.a',
              '<(webrtc_dir)/out/Release/librtc_xmpp.a',
              '<(webrtc_dir)/out/Release/librtc_p2p.a',
              '<(webrtc_dir)/out/Release/libusrsctplib.a',
              '<(webrtc_dir)/out/Release/libvideo_capture_module_internal_impl.a',
              '<(webrtc_dir)/out/Release/libvideo_render_module_internal_impl.a',
              '<(webrtc_dir)/out/Release/libjingle_p2p.a',
              '<(webrtc_dir)/out/Release/libsrtp.a',
              '<(webrtc_dir)/out/Release/libsocketrocket.a',
              '-lc++',
              '-framework ApplicationServices',
              '-lm',
              '-framework AudioToolbox',
              '-framework CoreAudio',
              '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/lib/libicucore.dylib',
            ],
          }
        }],
      ],
    }],
  'conditions': [
    ['OS=="linux" or OS=="android"', {
      'targets': [
        {
          'target_name': 'libpeeracle_so',
          'type': 'shared_library',
          'cflags': [
            '-fPIC'
          ],
          'dependencies': [
            'peeracle',
          ],
          'include_dirs': [
            '<(java_home)/include',
            '<(java_home)/include/linux',
          ],
          'sources': [
            'java/jni/peeracle_jni.c',
          ],
          'conditions': [
            ['OS=="android"', {
              'variables': {
                # This library uses native JNI exports; tell GYP so that the
                # required symbols will be kept.
                'use_native_jni_exports': 1,
              },
            }],
          ],
        },
        {
          'target_name': 'libpeeracle_jar',
          'type': 'none',
          'actions': [
            {
              'variables': {
                'java_src_dir': 'java/src',
                'build_jar_log': '<(INTERMEDIATE_DIR)/build_jar.log',
                'peeracle_java_files': [
                  'java/src/org/peeracle/DataSource.java',
                  'java/src/org/peeracle/HttpDataSource.java',
                  'java/src/org/peeracle/FileDataSource.java',
                ],
                'android_java_files': [
                ],
              },
              'action_name': 'create_jar',
              'inputs': [
                '<(DEPTH)/build/build_jar.sh',
                '<@(java_files)',
              ],
              'outputs': [
                '<(PRODUCT_DIR)/libpeeracle.jar',
              ],
              'conditions': [
                ['OS=="android"', {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)', '<@(android_java_files)'],
                    'build_classpath': '<(java_src_dir):<(DEPTH)/third_party/android_tools/sdk/platforms/android-<(android_sdk_version)/android.jar',
                  },
                }, {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)'],
                    'build_classpath': '<(java_src_dir)',
                  },
                }],
              ],
              'action': [
                'bash', '-ec',
                'mkdir -p <(INTERMEDIATE_DIR) && '
                '{ <(DEPTH)/build/build_jar.sh <(java_home) <@(_outputs) '
                '      <(INTERMEDIATE_DIR)/build_jar.tmp '
                '      <(build_classpath) <@(java_files) '
                '      > <(build_jar_log) 2>&1 || '
                '  { cat <(build_jar_log) ; exit 1; } }'
              ],
            },
          ],
          'dependencies': [
            'libpeeracle_so',
          ],
        },
      ],
    }],
  ],
}
