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
      'target_name': 'PeeracleDemo',
      'type': 'executable',
      'product_name': 'PeeracleDemo',
      'mac_bundle': 1,
      'dependencies': [
        '../../objc/peeracle_objc.gyp:*',
      ],
      'all_dependent_settings': {
        'xcode_settings': {
          'CLANG_ENABLE_OBJC_ARC': 'YES',
        },
      },
      'xcode_settings': {
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        # common.gypi enables this for mac but we want this to be disabled
        # like it is for ios.
        'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'NO',
      },
      'conditions': [
        ['OS=="ios"', {
          'mac_bundle_resources': [
          ],
          'sources': [
            'ios/main.m',
          ],
          'xcode_settings': {
            'INFOPLIST_FILE': 'ios/Info.plist',
          },
        }],
        ['OS=="mac"', {
          'sources': [
            'mac/main.m',
          ],
          'xcode_settings': {
            'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'NO',
            'INFOPLIST_FILE': 'mac/Info.plist',
            'MACOSX_DEPLOYMENT_TARGET' : '10.8',
            'OTHER_LDFLAGS': [
              '-framework AVFoundation',
            ],
          },
        }],
        ['target_arch=="ia32"', {
          'dependencies' : [
            '<(webrtc_depot_dir)/testing/iossim/iossim.gyp:iossim#host',
          ],
        }],
      ],
    },
  ],
}