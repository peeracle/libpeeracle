{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_media',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
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
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'MP3Media_unittest.cc',
        'MP4Media_unittest.cc',
        'WebMMedia_unittest.cc',
      ],
    },
  ],
}
