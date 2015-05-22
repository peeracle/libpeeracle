#!/bin/sh
set -e;

function check_depot_tools() {
    command -v ninja >/dev/null 2>&1 || {
	echo "ninja is not installed, fetching depot_tools";
	git submodule init third_party/depot_tools;
	git submodule update third_party/depot_tools;
	export PATH=`pwd`/third_party/depot_tools:$PATH;
    }
}

function check_gyp() {
    command -v gyp >/dev/null 2>&1 || {
	echo "gyp is not installed, fetching it";
	git submodule init third_party/gyp;
	git submodule update third_party/gyp;
	export PATH=`pwd`/third_party/gyp:$PATH;
    }
}

function fetch_webrtc() {
    git submodule init third_party/webrtc;
    git submodule update third_party/webrtc;
}

function build_webrtc() {
    cd third_party/webrtc;
    tools/clang/scripts/update.sh;
    webrtc/build/gyp_webrtc;
    ninja -C out/Release;
}

function run_gyp() {
    cd ../..;
    ./gyp.sh;
}

check_depot_tools;
check_gyp;
fetch_webrtc;
build_webrtc;
run_gyp;
