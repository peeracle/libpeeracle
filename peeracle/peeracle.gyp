{
  'variables': {
    'target_arch%': 'x64',
    'configuration%': 'Release',
    'peeracle_dir': '<!(echo `pwd`)/peeracle',
    'webrtc_dir': '<!(echo `pwd`)/../third_party/webrtc',
    'conditions': [
      ['OS=="android" or OS=="linux"', {
        'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); assert os.path.exists(os.path.join(dir, \'include/jni.h\')), \'Point \\$JAVA_HOME or the java_home gyp variable to a directory containing include/jni.h!\'; print dir")',
      }],
    ],
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
    }],
  'conditions': [
    ['OS=="linux" or OS=="android"', {
      'targets': [
        {
          'target_name': 'libpeeracle_so',
          'type': 'shared_library',
          'cflags': [
            '-fPIC'
          ],
          'dependencies': [
            'peeracle',
          ],
          'include_dirs': [
            '<(java_home)/include',
            '<(java_home)/include/linux',
          ],
          'sources': [
            'java/jni/peeracle_jni.c',
          ],
          'conditions': [
            ['OS=="android"', {
              'variables': {
                # This library uses native JNI exports; tell GYP so that the
                # required symbols will be kept.
                'use_native_jni_exports': 1,
              },
            }],
          ],
        },
        {
          'target_name': 'libpeeracle_jar',
          'type': 'none',
          'actions': [
            {
              'variables': {
                'java_src_dir': 'java/src',
                'build_jar_log': '<(INTERMEDIATE_DIR)/build_jar.log',
                'peeracle_java_files': [
                  'java/src/org/peeracle/DataSource.java',
                  'java/src/org/peeracle/HttpDataSource.java',
                  'java/src/org/peeracle/FileDataSource.java',
                ],
                'android_java_files': [
                ],
              },
              'action_name': 'create_jar',
              'inputs': [
                '<(DEPTH)/build/build_jar.sh',
                '<@(java_files)',
              ],
              'outputs': [
                '<(PRODUCT_DIR)/libpeeracle.jar',
              ],
              'conditions': [
                ['OS=="android"', {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)', '<@(android_java_files)'],
                    'build_classpath': '<(java_src_dir):<(DEPTH)/third_party/android_tools/sdk/platforms/android-<(android_sdk_version)/android.jar',
                  },
                }, {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)'],
                    'build_classpath': '<(java_src_dir)',
                  },
                }],
              ],
              'action': [
                'bash', '-ec',
                'mkdir -p <(INTERMEDIATE_DIR) && '
                '{ <(DEPTH)/build/build_jar.sh <(java_home) <@(_outputs) '
                '      <(INTERMEDIATE_DIR)/build_jar.tmp '
                '      <(build_classpath) <@(java_files) '
                '      > <(build_jar_log) 2>&1 || '
                '  { cat <(build_jar_log) ; exit 1; } }'
              ],
            },
          ],
          'dependencies': [
            'libpeeracle_so',
          ],
        },
      ],
    }],
  ],
}
