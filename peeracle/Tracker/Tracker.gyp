{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker',
      'type': 'none',
      'dependencies': [
        '<(DEPTH)/third_party/libwebsockets/libwebsockets.gyp:*',
        'Client/TrackerClient.gyp:*',
        'Message/TrackerMessage.gyp:*',
        'Server/TrackerServer.gyp:*'
      ],
    },
  ],
}
