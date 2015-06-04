{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_media',
      'type': 'static_library',
      'sources': [
        'MediaInterface.h',
        'MP3Media.cc',
        'MP3Media.h',
        'MP4Media.cc',
        'MP4Media.h',
        'WebMMedia.cc',
        'WebMMedia.h',
      ]
    },
    {
      'target_name': 'peeracle_media_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_media',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'sources': [
        'MP3Media_unittest.cc',
        'MP4Media_unittest.cc',
        'WebMMedia_unittest.cc',
      ],
    },
  ],
}
