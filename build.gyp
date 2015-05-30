{
  'includes': [
    'common.gypi'
  ],
  'variables': {
    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); print dir if os.path.exists(os.path.join(dir, \'include/jni.h\')) else 0")',
  },
  'targets': [
    {
      'target_name': 'build',
      'type': 'none',
      'dependencies': [
        'src/peeracle/peeracle.gyp:*',
        'samples/samples.gyp:*',
        'test/test.gyp:*',
      ],
      'conditions': [
        ['java_home!=0', {
          'dependencies': [
            'java/java.gyp:*',
          ],
        }],
      ],
    },
  ]
}