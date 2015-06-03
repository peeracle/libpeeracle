{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'peeracle_tracker',
      'type': 'none',
      'dependencies': [
        'Client/TrackerClient.gyp:*',
        'Message/TrackerMessage.gyp:*',
        'Server/TrackerServer.gyp:*'
      ],
    },
  ],
}
