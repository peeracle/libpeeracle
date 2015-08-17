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
        'third_party/lzstringpp/lzstringpp.gyp:*'
      ],
      'conditions': [
        ['OS == "ios" or OS == "mac"', {
          'dependencies': [
            'objc/peeracle_objc.gyp:*',
          ],
        }],
        ['build_java == 1 and java_home != 0', {
          'dependencies': [
            'java/java.gyp:*',
          ],
        }]
      ],
    },
  ]
}
