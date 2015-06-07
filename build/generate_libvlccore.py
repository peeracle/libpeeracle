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
import re
import subprocess
import sys
import tempfile
from optparse import OptionParser

DEFAULT_VLC_DIR = 'C:\\Program Files (x86)\\VideoLAN\\VLC'
DEFAULT_VC_BINDIR = 'C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\bin'

usage = 'usage: %prog [options]'
parser = OptionParser(usage=usage)

parser.add_option('--target-arch', default='x86',
                  help='target architecture, x86 or x64 are supported')

parser.add_option('--vlc-dir', default=DEFAULT_VLC_DIR,
                  help='path to VLC \'include\' and \'lib\' folders')

parser.add_option('--vc-bin-dir', default=DEFAULT_VC_BINDIR,
                  help='path to Visual Studio\'s bin directory')

(options, args) = parser.parse_args()
vlc_dir = options.vlc_dir
vc_bin_dir = options.vc_bin_dir
target_arch = options.target_arch

if os.path.exists(vlc_dir + '\\sdk\\lib'):
  exit(0)

os.makedirs(vlc_dir + '\\sdk\\lib')

_EXPORT_RE = re.compile(r"""
  ^\s*(?P<ordinal>[0-9]+)  # The ordinal field.
  \s+(?P<hint>[0-9A-F]+)   # The hint field.
  \s(?P<rva>........)      # The RVA field.
  \s+(?P<name>[^ ]+)       # And finally the name we're really after.
""", re.VERBOSE)

print 'Generating libvlccore.def...'
output = subprocess.Popen(vc_bin_dir + '\\dumpbin /EXPORTS "' +
                          vlc_dir + '\\libvlccore.dll"',
                          shell=False, stdout=subprocess.PIPE).stdout.read()
lines = output.split('\r\n')

exportsFile = open('libvlccore.def', 'w')
exportsFile.write('EXPORTS\n')
for line in lines:
  match = _EXPORT_RE.match(line)
  if match:
    export_name = match.group('name')
    if export_name:
      exportsFile.write(export_name + '\n')
exportsFile.close()

print 'Creating libvlccore.lib...'
output = subprocess.call(vc_bin_dir + '\\lib /def:"libvlccore.def" ' +
                        '/out:"' + vlc_dir + '\\sdk\\lib\\libvlccore.lib" ' +
                        '/machine:' + target_arch,
                        shell=False)

exit(output)
