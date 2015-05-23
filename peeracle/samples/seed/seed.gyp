{
  'targets': [
    {
      'target_name': 'seed',
      'type': 'executable',
      'dependencies': [
        '../../peeracle.gyp:peeracle'
      ],
      'sources': [
        'main.cc',
      ],
      'include_dirs': [
        '../../lib',
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
        }],
      ],
    }
  ]
}