#
# Copyright (c) 2015 peeracle contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

{
  'includes': [
    '../build/common.gypi'
  ],
  'variables': {
    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); print dir if os.path.exists(os.path.join(dir, \'include/jni.h\')) else 0")',
  },
  'targets': [
    {
      'target_name': 'peeracle_java',
      'type': 'none'
    },
  ],
  'conditions': [
    ['java_home!=0', {
      'targets': [
        {
          'target_name': 'libpeeracle_so',
          'type': 'shared_library',
          'dependencies': [
            '<(peeracle_root)/peeracle/peeracle.gyp:peeracle',
          ],
          'cflags': [
            '-fPIC'
          ],
          'include_dirs': [
            '<(java_home)/include',
            '<(java_home)/include/linux',
          ],
          'sources': [
            'jni/peeracle_jni.cc',
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
                  'src/org/peeracle/DataSource/DataSource.java',
                  'src/org/peeracle/DataSource/HttpDataSource.java',
                  'src/org/peeracle/DataSource/FileDataSource.java',
                ],
                'android_java_files': [
                ],
              },
              'action_name': 'create_jar',
              'inputs': [
                'scripts/build_jar.sh',
                '<@(java_files)',
              ],
              'outputs': [
                '<(PRODUCT_DIR)/libpeeracle.jar',
              ],
              'conditions': [
                ['OS=="android"', {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)', '<@(android_java_files)'],
                    'build_classpath': '<(java_src_dir):<(peeracle_root)/third_party/android_tools/sdk/platforms/android-<(android_sdk_version)/android.jar',
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
                '{ scripts/build_jar.sh <(java_home) <@(_outputs) '
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
