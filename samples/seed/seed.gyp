{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'seed',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/peeracle/peeracle.gyp:peeracle'
      ],
      'sources': [
        'src/main.cc',
      ],
      'conditions': [
        ['OS == "win"', {
          'defines': [
            'WEBRTC_WIN',
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': 0,
            },
          },
        }, {
          'defines': [
            'WEBRTC_POSIX',
          ],
        }],
        ['OS == "mac"', {
          'defines': [
            'WEBRTC_MAC',
          ],
          'xcode_settings': {
            'OTHER_CFLAGS': [
             '-std=c++11',
            ],
          },
        }],
      ],
    }
  ]
}