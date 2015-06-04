{
  'includes': [
    '../../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_client',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/third_party/libwebsockets/libwebsockets.gyp:*',
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
      'sources': [
        'TrackerClient_unittest.cc',
      ],
    },
  ],
}
