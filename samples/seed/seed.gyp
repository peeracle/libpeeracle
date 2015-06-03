{
  'includes': [
    '../../build/common.gypi',
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
    }
  ]
}