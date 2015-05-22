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
    }
  ]
}