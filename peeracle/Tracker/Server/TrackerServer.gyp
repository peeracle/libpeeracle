{
  'includes': [
    '../../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_server',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/third_party/libwebsockets/libwebsockets.gyp:*',
      ],
      'sources': [
        'TrackerServer.cc',
        'TrackerServer.h',
        'TrackerServerInterface.h',
      ]
    },
    {
      'target_name': 'peeracle_tracker_server_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_tracker_server',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'TrackerServer_unittest.cc',
      ],
    },
  ],
}
