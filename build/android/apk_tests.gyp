# Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS.  All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

# This file exists in two versions. A no-op version under
# webrtc/build/apk_tests_noop.gyp and this one. This gyp file builds the apk
# unit tests (for Android) assuming that WebRTC is built inside a Chromium
# workspace. The no-op version is included when building WebRTC without
# Chromium. This is a workaround for the fact that 'includes' don't expand
# variables and that the relative location of apk_test.gypi is different for
# WebRTC when built as part of Chromium and when it is built without Chromium.
{
  'includes': [
    '../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle_datastream_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_datastream_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_datastream_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/DataStream/DataStream.gyp:peeracle_datastream_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_hash_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_hash_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_hash_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Hash/Hash.gyp:peeracle_hash_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_media_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_media_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_media_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Media/Media.gyp:peeracle_media_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_metadata_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_metadata_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_metadata_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Metadata/Metadata.gyp:peeracle_metadata_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_peer_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_peer_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_peer_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Peer/Peer.gyp:peeracle_peer_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_session_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_session_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_session_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Session/Session.gyp:peeracle_session_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_websocketsclient_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_websocketsclient_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_websocketsclient_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/WebSocketsClient/WebSocketsClient.gyp:peeracle_websocketsclient_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_tracker_client_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_tracker_client_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_tracker_client_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Tracker/Client/TrackerClient.gyp:peeracle_tracker_client_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_tracker_message_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_tracker_message_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_tracker_message_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Tracker/Message/TrackerMessage.gyp:peeracle_tracker_message_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'peeracle_utils_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'peeracle_utils_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)peeracle_utils_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/peeracle/Utils/Utils.gyp:peeracle_utils_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
    {
      'target_name': 'lzstringpp_unittest_apk',
      'type': 'none',
      'variables': {
        'test_suite_name': 'lzstringpp_unittest',
        'input_shlib_path': '<(SHARED_LIB_DIR)/<(SHARED_LIB_PREFIX)lzstringpp_unittest<(SHARED_LIB_SUFFIX)',
      },
      'dependencies': [
        '<(DEPTH)/third_party/lzstringpp/lzstringpp.gyp:lzstringpp_unittest',
      ],
      'includes': [
        '../../third_party/webrtc/build/apk_test.gypi',
      ],
    },
  ],
}


