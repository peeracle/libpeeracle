{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_hash',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
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
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'Crc32Hash_unittest.cc',
      ],
    },
  ],
}
