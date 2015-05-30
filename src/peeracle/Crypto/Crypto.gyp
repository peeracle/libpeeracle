{
  'includes': [
    '../../../common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_crypto',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)/include',
      ],
      'sources': [
        'Crc32Crypto.cc',

        '<(DEPTH)/include/peeracle/Crypto/Crc32Crypto.h',
        '<(DEPTH)/include/peeracle/Crypto/CryptoInterface.h',
      ]
    },
    {
      'target_name': 'peeracle_crypto_unittest',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'include_dirs': [
        '<(DEPTH)/include',
      ],
      'sources': [
        'Crc32Crypto_unittest.cc',
      ],
    },
  ],
}
