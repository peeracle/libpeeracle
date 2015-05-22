{
  'variables': {
    'target_arch%': 'x64',
    'configuration%': 'Release',
    'peeracle_dir': '<!(echo `pwd`)/peeracle',
    'webrtc_dir': '<!(echo `pwd`)/../third_party/webrtc',
  },
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'cflags': [
        '-std=c++11',
        '-fPIC'
      ],
      'defines': [
        'WEBRTC_POSIX=1'
      ],
      'sources': [
        'lib/createanswerobserver.cc',
        'lib/createofferobserver.cc',
        'lib/createsessiondescriptionobserver.cc',
        'lib/manager.cc',
        'lib/peer.cc',
        'lib/setanswerobserver.cc',
        'lib/setlocalofferobserver.cc',
        'lib/setremoteofferobserver.cc',
        'lib/setsessiondescriptionobserver.cc',
      ],
      'include_dirs': [
          '<(webrtc_dir)',
          '<(webrtc_dir)/third_party',
      ],
      'link_settings': {
        'libraries': [
          '-Wl,--start-group',
          '<!@(find <(webrtc_dir)/out/Release -name *.a -type f)',
          '-lpthread',
          '-ldl',
          '-lnss3',
          '-lnssutil3',
          '-lplc4',
          '-lnspr4',
          '-lX11',
          '-Wl,--end-group'
        ],
      },
    },
  ],
}
