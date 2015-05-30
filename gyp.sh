#!/bin/sh
set -e;

gyp build.gyp -f ninja -Dconfiguration=Release --no-circular-check --check -Ithird_party/webrtc/webrtc/build/common.gypi -Ithird_party/webrtc/webrtc/supplement.gypi --depth=.
