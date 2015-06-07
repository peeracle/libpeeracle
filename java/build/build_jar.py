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

import os
import shutil
import subprocess
import sys
sys.argv[0] + ": Entering directory \``pwd`'"

if len(sys.argv) < 6:
  print ("Usage: " + sys.argv[0] + " jar-name temp-work-dir source-path-dir "
        ".so-to-bundle classpath Source1.java Source2.java ..")
  exit(1)

JAVA_HOME=sys.argv[1]
JAR_NAME=sys.argv[2]
TMP_DIR=sys.argv[3]
CLASSPATH=sys.argv[4]

if not os.path.exists(TMP_DIR):
  os.makedirs(TMP_DIR)
TMP_DIR += '/build_jar.tmp'

shutil.rmtree(TMP_DIR, True)
os.mkdir(TMP_DIR)

args = [JAVA_HOME + '/bin/javac',
        '-Xlint:deprecation',
        '-Xlint:unchecked',
        '-d', TMP_DIR,
        '-classpath', CLASSPATH]

result = subprocess.call(args + sys.argv[5:])
if result:
  exit(result)

result = subprocess.call([JAVA_HOME + '/bin/jar',
                          'cf', JAR_NAME, '-C', TMP_DIR, '.'])
exit(result)
