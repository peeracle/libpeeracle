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
    '../../third_party/webrtc/webrtc/build/common.gypi',
    '../../build/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle_peer',
      'type': 'static_library',
      'standalone_static_library': 1,
      'dependencies': [
        '<(webrtc_depth)/talk/libjingle.gyp:libjingle_peerconnection',
        '../Tracker/Client/TrackerClient.gyp:peeracle_tracker_client',
      ],
      'defines': [
        'BUILD_LIBPEERACLE',
      ],
      'sources': [
        'CreateSDPObserver.cc',
        'DataChannelObserver.cc',
        'Observer.cc',
        'PeerInterface.h',
        'Peer.cc',
        'Peer.h',
        'PeerImpl.cc',
        'PeerImpl.h',
        'SetLocalSDPObserver.cc',
        'SetRemoteSDPObserver.cc',
      ],
      'includes': [
        '../../build/lint.gypi',
      ],
    },
  ],
  'conditions': [
    ['build_tests == 1', {
      'targets': [
        {
          'target_name': 'peeracle_peer_unittest',
          'type': '<(gtest_target_type)',
          'dependencies': [
            'peeracle_peer',
            '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
          ],
          'conditions': [
            ['OS=="android"', {
              'dependencies': [
                '<(DEPTH)/java/java.gyp:libpeeracle',
                '<(webrtc_depth)/testing/android/native_test.gyp:native_test_native_code',
              ],
            }],
          ],
          'defines': [
            'BUILD_LIBPEERACLE',
          ],
          'sources': [
            '../peeracle.cc',
            'Peer_unittest.cc',
          ],
          'includes': [
            '../../build/lint.gypi',
          ],
        },
      ],
      'conditions': [
        ['OS=="android"', {
          'targets': [
            {
              'target_name': 'peeracle_peer_unittest_apk_target',
              'type': 'none',
              'dependencies': [
                '<(apk_tests_path):peeracle_peer_unittest_apk',
              ],
            },
          ],
        }],
        ['test_isolation_mode != "noop"', {
          'targets': [
            {
              'target_name': 'peeracle_peer_unittest_run',
              'type': 'none',
              'dependencies': [
                'peeracle_peer_unittest',
              ],
              'includes': [
                '../../build/isolate.gypi',
              ],
              'sources': [
                'peeracle_peer_unittest.isolate',
              ],
            },
          ],
        }]
      ],
    }],
  ],
}
