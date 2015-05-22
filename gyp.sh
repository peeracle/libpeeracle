#!/bin/sh
set -e;
gyp -f make --depth=. build.gyp;
