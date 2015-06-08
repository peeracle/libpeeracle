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
  ],
  'variables': {
    'conditions': [
      ['OS == "win"', {
        'vlc_path%': '<!(python -c "import os; dir=os.getenv(\'VLC_PATH\', \'C:/Program Files (x86)/VideoLAN/VLC/sdk\'); print dir if os.path.exists(os.path.join(dir, \'include/vlc/plugins/vlc_plugin.h\')) else 0")',
      }, {
        'vlc_path%': '<!(bash -ec "pkg-config vlc-plugin && echo 1 || echo 0")',
      }],
    ],
  },
  'conditions': [
    ['vlc_path != 0', {
      'targets': [
        {
          'target_name': 'libpeeracle_plugin',
          'type': 'shared_library',
          'dependencies': [
            '<(DEPTH)/peeracle/peeracle.gyp:peeracle',
          ],
          'sources': [
            'plugin.cc',
            'PeeracleManager.cc',
            'PeeracleStream.cc',
            'VLCDataStream.cc',
          ],
          'include_dirs': [
            'config/<(OS)/<(target_arch)',
          ],
          'conditions': [
            ['OS == "win"', {
              'defines': [
                'HAVE_CONFIG_H',
                '__PLUGIN__',
              ],
              'include_dirs': [
                '<(vlc_path)\\include\\vlc\\plugins',
              ],
              'msvs_settings': {
                'VCLinkerTool': {
                  'AdditionalLibraryDirectories': [
                    '<(vlc_path)\\lib',
                  ],
                  'AdditionalDependencies': [
                    'libvlccore.lib'
                  ],
                  'ImageHasSafeExceptionHandlers': 'false',
                },
                'MASM': {
                  'UseSafeExceptionHandlers': 'false',
                },
              },
            }],
            ['OS == "linux"', {
              'include_dirs': [
                '<!@(pkg-config vlc-plugin --cflags-only-I | sed s/-I//g)'
              ],
              'libraries': [
                '<!@(pkg-config vlc-plugin --libs)'
              ],
            }],
            ['OS == "mac"', {
              'defines': [
                'HAVE_CONFIG_H',
                '<!@(pkg-config vlc-plugin --cflags-only-other | sed s/-D//g)',
              ],
              'include_dirs': [
                '<!@(pkg-config vlc-plugin --cflags-only-I | sed s/-I//g)'
              ],
              'libraries': [
                '<!@(pkg-config vlc-plugin --libs)',
                '-framework Cocoa',
                '-liconv'
              ],
            }],
          ],
        }
      ]}, {
        'targets': [
          {
            'target_name': 'libpeeracle_plugin',
            'type': 'none'
          },
        ],
      }
    ],
  ],
}
