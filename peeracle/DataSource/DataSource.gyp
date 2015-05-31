{
  'includes': [
    '../../common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_datasource',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'DataSourceInterface.h',
        'FileDataSource.cc',
        'FileDataSource.h',
        'HttpDataSource.cc',
        'HttpDataSource.h',
      ]
    },
    {
      'target_name': 'peeracle_datasource_unittest',
      'type': '<(gtest_target_type)',
      'dependencies': [
        'peeracle_datasource',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'FileDataSource_unittest.cc',
        'HttpDataSource_unittest.cc',
      ],
    },
  ],
}
