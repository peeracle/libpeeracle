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
      'target_name': 'peeracle_metadata',
      'type': 'static_library',
      'sources': [
        'MetadataInterface.h',
        'Metadata.cc',
        'Metadata.h',
        'MetadataSerializerInterface.h',
        'MetadataSerializer.cc',
        'MetadataSerializer.h',
        'MetadataUnserializerInterface.h',
        'MetadataUnserializer.cc',
        'MetadataUnserializer.h',
      ]
    },
  ],
  'conditions': [
    ['build_tests == 1', {
      'targets': [
        {
          'target_name': 'peeracle_metadata_unittest',
          'type': 'executable',
          'dependencies': [
            'peeracle_metadata',
            '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
          ],
          'sources': [
            'Metadata_unittest.cc',
            'MetadataSerializer_unittest.cc',
            'MetadataUnserializer_unittest.cc',
          ],
        },
      ],
    }],
  ],
}
