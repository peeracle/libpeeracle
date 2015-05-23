#!/bin/sh
set -e;

gyp build.gyp -f ninja --no-circular-check --check -I`pwd`/third_party/webrtc/webrtc/build/common.gypi -I`pwd`/third_party/webrtc/webrtc/supplement.gypi --depth=.
