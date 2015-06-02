{
  'includes': [
    '../../../common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_client',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'TrackerClient.cc',
        'TrackerClient.h',
        'TrackerClientInterface.h',
      ]
    },
    {
      'target_name': 'peeracle_tracker_client_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_tracker_client',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'TrackerClient_unittest.cc',
      ],
    },
  ],
}
