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
        '<(DEPTH)/testing/gtest.gyp:gtest',
      ],
      'direct_dependent_settings': {
        'defines': [
          'GTEST_RELATIVE_PATH',
        ],
        'include_dirs': [
          '<(DEPTH)/testing/gtest/include',
        ],
      },
      'export_dependent_settings': [
        '<(DEPTH)/testing/gtest.gyp:gtest',
      ],
    },
  ],
}
