{
  'includes': [
    '../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'dependencies': [
        'DataSource/DataSource.gyp:*',
        'Hash/Hash.gyp:*',
        'Media/Media.gyp:*',
        'Metadata/Metadata.gyp:*',
        'Tracker/Tracker.gyp:*',
      ],
      'sources': [
        'empty.cc',
      ],
    },
  ],
}
