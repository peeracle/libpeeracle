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
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'FileDataSource_unittest.cc',
        'HttpDataSource_unittest.cc',
      ],
    },
  ],
}
