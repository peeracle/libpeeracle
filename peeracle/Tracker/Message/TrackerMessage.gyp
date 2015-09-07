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
    '../../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_message',
      'type': 'static_library',
      'standalone_static_library': 1,
      'dependencies': [
        '<(DEPTH)/third_party/lzstringpp/lzstringpp.gyp:lzstringpp',
        '<(webrtc_depth)/third_party/jsoncpp/jsoncpp.gyp:jsoncpp',
        '../../DataStream/DataStream.gyp:peeracle_datastream',
      ],
      'sources': [
        'TrackerMessage.cc',
        'TrackerMessage.h',
        'TrackerMessageInterface.h',
      ],
      'includes': [
        '../../../build/lint.gypi',
      ],
    },
  ],
  'conditions': [
    ['build_tests == 1', {
      'targets': [
        {
          'target_name': 'peeracle_tracker_message_unittest',
          'type': '<(gtest_target_type)',
          'dependencies': [
            'peeracle_tracker_message',
            '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
          ],
          'conditions': [
            ['OS=="android"', {
              'dependencies': [
                '<(webrtc_depth)/testing/android/native_test.gyp:native_test_native_code',
              ],
            }],
          ],
          'sources': [
            'TrackerMessage_unittest.cc',
          ],
          'includes': [
            '../../../build/lint.gypi',
          ],
        },
      ],
      'conditions': [
        ['OS=="android"', {
          'targets': [
            {
              'target_name': 'peeracle_tracker_message_unittest_apk_target',
              'type': 'none',
              'dependencies': [
                '<(apk_tests_path):peeracle_tracker_message_unittest_apk',
              ],
            },
          ],
        }],
        ['test_isolation_mode != "noop"', {
          'targets': [
            {
              'target_name': 'peeracle_tracker_message_unittest_run',
              'type': 'none',
              'dependencies': [
                'peeracle_tracker_message_unittest',
              ],
              'includes': [
                '../../../build/isolate.gypi',
              ],
              'sources': [
                'peeracle_tracker_message_unittest.isolate',
              ],
            },
          ],
        }]
      ],
    }],
  ],
}
