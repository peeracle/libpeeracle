# libpeeracle

[![Travis-CI](https://travis-ci.org/peeracle/libpeeracle.svg)](https://travis-ci.org/peeracle/libpeeracle) [![Build status](https://ci.appveyor.com/api/projects/status/a5pf8w7c60vssv5c?svg=true)](https://ci.appveyor.com/project/aisouard/libpeeracle)

### Peer-to-Peer Video on Demand for all

This is the C++ version of the [Peeracle library](https://github.com/peeracle/peeracle),
with Objective-C and Java bindings for iOS and Android applications.

## Topics

* [Setting up the Development Environment](#setting-up-the-development-environment)
  * [Prerequisites](#prerequisites)
    * [General](#general)
    * [Windows](#windows)
    * [Mac OS X](#mac-os-x)
  * [Getting the source code](#getting-the-source-code)
  * [Compiling](#compiling)

## Setting up the Development Environment

### Prerequisites

#### General
- Python 2.7.6

#### Windows
- Shell prompt, such as msys, Msysgit or Cygwin
- Microsoft Visual Studio 2013 - [download Community Edition](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx)
- Microsoft DirectX SDK - [download](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

#### Mac OS X
- XCode

### Getting the source code

First, clone the repository

```bash
$ git clone https://github.com/peeracle/libpeeracle.git
```

Init the submodules

```bash
$ git submodule init
$ git submodule update
```

Windows users **MUST** build the symbolic links inside the WebRTC repository

```cmd
python third_party\webrtc\setup_links.py
```

Add depot_tools to your PATH environment variable

- Linux, Mac OS X
```bash
$ export PATH=$PATH:`pwd`/third_party/depot_tools
```

- Windows
```cmd
> set PATH=%PATH%;%cd%\third_party\depot_tools
```

### Compiling

Generate the build scripts everytime you edit a GYP file, these commands
**MUST** be run from the Windows Command Prompt if you are using Windows.

```
python gyp_peeracle.py
```

Then build

```
ninja -C out/Release
```
