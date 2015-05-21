#!/bin/sh
set -e;

function check_depot_tools() {
    echo "ninja is not installed, fetching depot_tools";
    git submodule init third_party/depot_tools;
    git submodule update third_party/depot_tools;
    export PATH=`pwd`/third_party/depot_tools:$PATH;
}

function fetch_webrtc() {
    git submodule init third_party/webrtc;
    git submodule update third_party/webrtc;
}

command -v ninja >/dev/null 2>&1 || check_depot_tools;
fetch_webrtc;
cd third_party/webrtc;
tools/clang/scripts/update.sh;
webrtc/build/gyp_webrtc;
ninja -C out/Release;
