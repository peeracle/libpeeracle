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
        'vlc-plugin/vlc-plugin.gyp:*'
      ],
    }
  ]
}