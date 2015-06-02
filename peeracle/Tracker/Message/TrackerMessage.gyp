{
  'includes': [
    '../../../common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker_message',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
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
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'TrackerMessage_unittest.cc',
      ],
    },
  ],
}
