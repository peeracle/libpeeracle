{
  'includes': [
    '../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle_tests_utils',
      'type': 'static_library',
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'unittest_main.cc',
      ],
      'defines': [
        'GTEST_RELATIVE_PATH',
      ],
      'dependencies': [
        '<(DEPTH)/third_party/googletest/gtest.gyp:gtest',
      ],
      'direct_dependent_settings': {
        'defines': [
          'GTEST_RELATIVE_PATH',
        ],
        'include_dirs': [
          '<(DEPTH)/third_party/googletest/gtest/include',
        ],
      },
      'export_dependent_settings': [
        '<(DEPTH)/third_party/googletest/gtest.gyp:gtest',
      ],
    },
  ],
}
