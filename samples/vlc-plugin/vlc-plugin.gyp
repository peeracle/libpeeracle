{
  'includes': [
    '../../build/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle_plugin',
      'type': 'shared_library',
      'defines': [
        '__PLUGIN__',
      ],
      'dependencies': [
        '<(DEPTH)/peeracle/peeracle.gyp:peeracle',
        '<(DEPTH)/third_party/vlc/vlc.gyp:vlc'
      ],
      'sources': [
        'plugin.cc',
      ],
    }
  ]
}