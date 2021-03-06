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
  'variables': {
    'build_java%': 1,         # build Java bindings and samples
    'build_objc%': 1,         # build Objective-C bindings and samples
    'build_tests%': 1,        # build unit tests
    'build_samples%': 1,      # build samples
    'build_vlcplugin%': 1,    # build VLC plugin
    'use_curl%': 1,           # use cURL
    'use_libwebsockets%': 1,  # use libwebsockets
    'apk_tests_path%': '<(DEPTH)/build/android/apk_tests.gyp',
    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); print dir if os.path.exists(os.path.join(dir, \'include/jni.h\')) else 0")',
  },
  'target_defaults': {
    'defines': [
      'LIBPEERACLE_REVISION="<!(git describe --tag --always)"',
    ],
    'include_dirs': [
      '<(DEPTH)',
      '<(webrtc_depth)',
    ],
  },
}