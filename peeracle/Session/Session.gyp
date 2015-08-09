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
    '../../build/common.gypi',
    '../../third_party/webrtc/webrtc/build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_session',
      'type': 'static_library',
      'standalone_static_library': 1,
      'dependencies': [
        '../Peer/Peer.gyp:peeracle_peer',
        '../Tracker/Client/TrackerClient.gyp:peeracle_tracker_client'
      ],
      'sources': [
        'SessionInterface.h',
        'Session.cc',
        'Session.h',
        'SessionHandle.cc',
        'SessionHandle.h',
        'SessionHandleInterface.h',
        'SessionHandleObserver.h',
        'SessionObserver.h',
        'SessionPeerObserver.cc',
        'SessionPeerObserver.h',
        'SessionTrackerClientObserver.cc',
        'SessionTrackerClientObserver.h',
      ]
    },
  ],
  'conditions': [
    ['build_tests == 1', {
      'targets': [
        {
          'target_name': 'peeracle_session_unittest',
          'type': 'executable',
          'dependencies': [
            'peeracle_session',
            '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
          ],
          'sources': [
            'Session_unittest.cc',
          ],
        },
      ],
    }],
  ],
}
