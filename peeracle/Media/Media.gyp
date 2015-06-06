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
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_media',
      'type': 'static_library',
      'sources': [
        'MediaInterface.h',
        'MP3Media.cc',
        'MP3Media.h',
        'MP4Media.cc',
        'MP4Media.h',
        'WebMMedia.cc',
        'WebMMedia.h',
      ]
    },
    {
      'target_name': 'peeracle_media_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_media',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'MP3Media_unittest.cc',
        'MP4Media_unittest.cc',
        'WebMMedia_unittest.cc',
      ],
    },
  ],
}
