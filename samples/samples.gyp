{
  'includes': [
    '../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'samples',
      'type': 'none',
      'dependencies': [
        'seed/seed.gyp:*',
      ],
      'conditions': [
        ['OS == "win" or OS == "mac" or OS == "linux"', {
          'dependencies': [
            'vlc-plugin/vlc-plugin.gyp:*'
          ],
        }],
      ],
    }
  ]
}
