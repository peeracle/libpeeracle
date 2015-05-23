{
  'includes': [
    'build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'build',
      'type': 'none',
      'dependencies': [
        'peeracle/peeracle.gyp:*',
        'peeracle/samples/samples.gyp:*',
      ],
    },
  ]
}