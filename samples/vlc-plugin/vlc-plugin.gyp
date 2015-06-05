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