#!/usr/bin/env python
# Copyright (c) 2014 The WebRTC project authors. All Rights Reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS.  All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

"""
Runs tests on Android devices.

This script exists to avoid WebRTC being broken by changes in the Chrome Android
test execution toolchain. It also conveniently sets the CHECKOUT_SOURCE_ROOT
environment variable.
"""

import os
import sys

SCRIPT_DIR = os.path.dirname(__file__)
SRC_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, os.pardir, os.pardir))

CHROMIUM_BUILD_ANDROID_DIR = os.path.join(SRC_DIR, 'third_party', 'webrtc',
                                          'build', 'android')

CHROMIUM_ANDROID_TESTRUNNER_DIR = os.path.join(SRC_DIR, 'third_party', 'webrtc',
                                               'chromium', 'src', 'third_party',
                                               'android_testrunner')

CHROMIUM_APPURIFY_DIR = os.path.join(SRC_DIR, 'third_party', 'webrtc',
                                     'chromium', 'src', 'third_party',
                                     'appurify-python', 'src')

CHROMIUM_LIB_COMMON = os.path.join(SRC_DIR, 'third_party', 'webrtc',
                                   'chromium', 'src', 'build', 'util',
                                   'lib', 'common')

sys.path.insert(0, CHROMIUM_BUILD_ANDROID_DIR)
sys.path.insert(0, CHROMIUM_ANDROID_TESTRUNNER_DIR)
sys.path.insert(0, CHROMIUM_APPURIFY_DIR)
sys.path.insert(0, CHROMIUM_LIB_COMMON)


import test_runner  # pylint: disable=W0406
from pylib.gtest import gtest_config
from pylib.gtest import setup

def main():
  # Override the stable test suites with the WebRTC tests.
  gtest_config.STABLE_TEST_SUITES = [
    'peeracle_datastream_unittest',
  ]
  gtest_config.EXPERIMENTAL_TEST_SUITES = []

  # Set our own paths to the .isolate files.
  setup.ISOLATE_FILE_PATHS = {
    'peeracle_datastream_unittest':
        'peeracle/DataStream/peeracle_datastream_unittest.isolate'
  }
  # Override environment variable to make it possible for the scripts to find
  # the root directory (our symlinking of the Chromium build toolchain would
  # otherwise make them fail to do so).
  return test_runner.main()

if __name__ == '__main__':
  sys.exit(main())
