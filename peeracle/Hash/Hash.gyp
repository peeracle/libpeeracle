{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_hash',
      'type': 'static_library',
      'sources': [
        'HashInterface.h',
        'Crc32Hash.cc',
        'Crc32Hash.h',
      ]
    },
    {
      'target_name': 'peeracle_hash_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_hash',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'Crc32Hash_unittest.cc',
      ],
    },
  ],
}
