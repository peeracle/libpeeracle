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
        'samples/samples.gyp:*',
        'test/test.gyp:*',
      ],
      'conditions': [
        ['java_home!=0', {
          'dependencies': [
            'java/java.gyp:*',
          ],
        }],
      ],
    },
  ]
}