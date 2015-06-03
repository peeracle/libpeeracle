{
  'includes': [
    '../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'include_dirs': [
        '<(DEPTH)',
      ],
      'dependencies': [
        #'<(DEPTH)/third_party/webrtc/talk/libjingle.gyp:*',
        'DataSource/DataSource.gyp:*',
        'Hash/Hash.gyp:*',
        'Media/Media.gyp:*',
        'Metadata/Metadata.gyp:*',
        'Tracker/Tracker.gyp:*',
      ],
    },
  ],
}
