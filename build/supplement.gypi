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
  'variables': {
    'variables': {
      'webrtc_root': '<(DEPTH)/third_party/webrtc/webrtc',
      'peeracle_root': '<(DEPTH)',
      'webrtc_depth': '<(DEPTH)/third_party/webrtc',
    },
    'webrtc_root': '<(webrtc_root)',
    'peeracle_root': '<(peeracle_root)',
    'webrtc_depth': '<(webrtc_depth)',
    'build_with_chromium': 0,
    'clang_use_chrome_plugins': 0,
    'conditions': [
      ['OS=="ios"', {
        # Default to using BoringSSL on iOS.
        'use_openssl%': 1,

        # Set target_subarch for if not already set. This is needed because the
        # Chromium iOS toolchain relies on target_subarch being set.
        'conditions': [
          ['target_arch=="arm" or target_arch=="ia32"', {
            'target_subarch%': 'arm32',
          }],
          ['target_arch=="arm64" or target_arch=="x64"', {
            'target_subarch%': 'arm64',
          }],
        ],
      }],
    ],
  },
  'target_defaults': {
    'target_conditions': [
      ['_target_name=="sanitizer_options"', {
        'conditions': [
          ['lsan==1', {
            # Replace Chromium's LSan suppressions with our own for WebRTC.
            'sources/': [
              ['exclude', 'lsan_suppressions.cc'],
            ],
            'sources': [
              '<(webrtc_root)/build/sanitizers/lsan_suppressions_webrtc.cc',
            ],
          }],
          ['tsan==1', {
            # Replace Chromium's TSan v2 suppressions with our own for WebRTC.
            'sources/': [
              ['exclude', 'tsan_suppressions.cc'],
            ],
            'sources': [
              '<(webrtc_root)/build/sanitizers/tsan_suppressions_webrtc.cc',
            ],
          }],
        ],
      }],
    ],
  },
}
