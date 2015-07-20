{
  'targets': [
    {
      'target_name': 'build',
      'type': 'none',
      'dependencies': [
        'peeracle/peeracle.gyp:*',
        'samples/samples.gyp:*',
        'test/test.gyp:*',
        'java/java.gyp:*',
        'third_party/lzstringpp/lzstringpp.gyp:*'
      ],
    },
  ]
}