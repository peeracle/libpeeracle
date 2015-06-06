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
    'vlc_path%': '<!(python -c "import os; dir=os.getenv(\'VLC_PATH\', \'/usr/local/etc/vlc\'); print dir if os.path.exists(os.path.join(dir, \'include/vlc/vlc.h\')) else 0")',
  },
  'targets': [
    {
      'target_name': 'peeracle_vlc_plugin',
      'type': 'none'
    },
  ],
  'conditions': [
    ['vlc_path!=0', {
      'targets': [
        {
          'target_name': 'libpeeracle_plugin',
          'type': 'shared_library',
          'defines': [
            '__PLUGIN__',
          ],
          'dependencies': [
            '<(DEPTH)/peeracle/peeracle.gyp:peeracle',
          ],
          'sources': [
            'plugin.cc',
          ],
          'conditions': [
            ['OS == "linux" or OS == "mac"', {
              'include_dirs': [
                '<(vlc_path)/include/vlc/plugins',
              ],
              'link_settings': {
                'libraries': [
                  '-L<(vlc_path)/lib',
                  '-lvlccore',
                ],
              },
            }],
            ['OS == "win"', {

            }],
          ],
        }
      ]
    }]
  ]
}