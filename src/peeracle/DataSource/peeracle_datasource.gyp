{
  'includes': [
    '../../../common.gypi'
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
        '<(DEPTH)/include',
      ],
      'sources': [
        'FileDataSource.cc',
        'HttpDataSource.cc',

        '<(DEPTH)/include/peeracle/DataSource/HttpDataSource.h',
        '<(DEPTH)/include/peeracle/DataSource/FileDataSource.h',
        '<(DEPTH)/include/peeracle/DataSource/DataSourceInterface.h',
      ]
    },
    {
      'target_name': 'peeracle_datasource_unittest',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'include_dirs': [
        '<(DEPTH)/include',
      ],
      'sources': [
        'FileDataSource_unittest.cc',
        'HttpDataSource_unittest.cc',
      ],
    },
  ],
}
