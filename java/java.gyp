#
# Copyright (c) 2015 peeracle contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

{
  'includes': [
    '../third_party/webrtc/webrtc/build/common.gypi',
    '../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'libpeeracle',
      'type': 'shared_library',
      'dependencies': [
        '<(webrtc_depth)/third_party/icu/icu.gyp:icuuc',
        '<(DEPTH)/peeracle/DataStream/DataStream.gyp:peeracle_datastream',
        '<(DEPTH)/peeracle/Hash/Hash.gyp:peeracle_hash',
        '<(DEPTH)/peeracle/Media/Media.gyp:peeracle_media',
        '<(DEPTH)/peeracle/Metadata/Metadata.gyp:peeracle_metadata',
        '<(DEPTH)/peeracle/Peer/Peer.gyp:peeracle_peer',
        '<(DEPTH)/peeracle/Session/Session.gyp:peeracle_session',
        '<(DEPTH)/peeracle/Tracker/Client/TrackerClient.gyp:peeracle_tracker_client',
        '<(DEPTH)/peeracle/Tracker/Message/TrackerMessage.gyp:peeracle_tracker_message',
        '<(DEPTH)/peeracle/Utils/Utils.gyp:peeracle_randomgenerator',
      ],
      'cflags': [
        '-fPIC'
      ],
      'include_dirs': [
        '<(java_home)/include',
        '<(java_home)/include/linux',
      ],
      'defines': [
        'BUILD_LIBPEERACLE',
      ],
      'sources': [
        'jni/peeracle_jni.cc',
        'jni/datastream_jni.cc',
        '../peeracle/peeracle.cc',
      ],
      'includes': [
        '../build/lint.gypi',
      ],
      'conditions': [
        ['OS=="android"', {
          'dependencies': [
            'android_websocketsclient',
          ],
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
              'src/org/peeracle/DataStream.java'
            ],
            'android_java_files': [
            ],
          },
          'action_name': 'create_jar',
          'outputs': [
            '<(PRODUCT_DIR)/libpeeracle.jar',
          ],
          'conditions': [
            ['OS=="android"', {
              'variables': {
                'java_files': ['<@(peeracle_java_files)', '<@(android_java_files)'],
                'build_classpath': '<(java_src_dir):<(peeracle_root)/third_party/android_sdk/platforms/android-<(android_sdk_version)/android.jar',
              },
            }, {
              'variables': {
                'java_files': ['<@(peeracle_java_files)'],
                'build_classpath': '<(java_src_dir)',
              }
            }],
          ],
          'inputs': [
            'build/build_jar.sh',
            '<@(java_files)',
          ],
          'action': [
            'bash', '-ec',
            'mkdir -p <(INTERMEDIATE_DIR) && '
            '{ build/build_jar.sh <(java_home) <@(_outputs) '
            '      <(INTERMEDIATE_DIR)/build_jar.tmp '
            '      <(build_classpath) <@(java_files) '
            '      > <(build_jar_log) 2>&1 || '
            '  { cat <(build_jar_log) ; exit 1; } }'
          ],
        },
      ],
      'dependencies': [
        'libpeeracle',
      ],
    },
  ],
  'conditions': [
    ['OS=="android"', {
      'targets': [
        {
          'target_name': 'libpeeracle_java',
          'type': 'none',
          'dependencies': [
            'libpeeracle',
          ],
          'variables': {
            'java_in_dir': '.',
            'additional_src_dirs' : [
            ],
          },
          'includes': ['../third_party/webrtc/build/java.gypi'],
        },
        {
          'target_name': 'android_websocketsclient',
          'type': 'static_library',
          'cflags': [
            '-fPIC'
          ],
          'include_dirs': [
            '<(java_home)/include',
            '<(java_home)/include/linux',
          ],
          'sources': [
            'jni/WebSocketsClient_jni.h',
            'jni/WebSocketsClient_jni.cc',
          ],
          'includes': [
            '../build/lint.gypi',
          ],
          'variables': {
            # This library uses native JNI exports; tell GYP so that the
            # required symbols will be kept.
            'use_native_jni_exports': 1,
          },
        },
      ],
    }],
  ]
}
