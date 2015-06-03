{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_metadata',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'MetadataInterface.h',
        'Metadata.cc',
        'Metadata.h',
        'MetadataSerializerInterface.h',
        'MetadataSerializer.cc',
        'MetadataSerializer.h',
        'MetadataUnserializerInterface.h',
        'MetadataUnserializer.cc',
        'MetadataUnserializer.h',
      ]
    },
    {
      'target_name': 'peeracle_metadata_unittest',
      'type': 'executable',
      'dependencies': [
        'peeracle_metadata',
        '<(DEPTH)/test/test.gyp:peeracle_tests_utils',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        'Metadata_unittest.cc',
        'MetadataSerializer_unittest.cc',
        'MetadataUnserializer_unittest.cc',
      ],
    },
  ],
}
