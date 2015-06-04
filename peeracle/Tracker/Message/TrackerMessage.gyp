{
  'includes': [
    '../../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_message',
      'type': 'static_library',
      'sources': [
        'TrackerMessage.cc',
        'TrackerMessage.h',
        'TrackerMessageInterface.h',
      ]
    },
    {
      'target_name': 'peeracle_tracker_message_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_tracker_message',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'TrackerMessage_unittest.cc',
      ],
    },
  ],
}
