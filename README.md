# libpeeracle

[![Travis-CI](https://travis-ci.org/peeracle/libpeeracle.svg)](https://travis-ci.org/peeracle/libpeeracle) [![Coverity](https://scan.coverity.com/projects/5244/badge.svg)](https://scan.coverity.com/projects/5244)

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
    * [Cloning libpeeracle](#cloning-libpeeracle)
    * [Cloning depot_tools](#cloning-depot_tools)
    * [Cloning GYP](#cloning-gyp)
    * [WebRTC](#webrtc)
  * [Windows, Git and Symbolic Links](#windows-git-and-symbolic-links)
    * [Install the symlink script](#install-the-symlink-script)
  * [Compiling](#compiling)
    * [Compiling WebRTC](#compiling-webrtc)
    * [Compiling libpeeracle](#compiling-libpeeracle)

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

#### Cloning libpeeracle

First, clone the repository

```bash
$ git clone git@github.com:peeracle/libpeeracle
```

#### Cloning depot_tools

Retrieve [depot_tools](https://www.chromium.org/developers/how-tos/install-depot-tools) if you don't have it

```bash
$ git submodule init third_party/depot_tools
$ git submodule update third_party/depot_tools
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

#### Cloning GYP

The same goes for [GYP](https://chromium.googlesource.com/external/gyp) :

```bash
$ git submodule init third_party/gyp
$ git submodule update third_party/gyp
```

- Linux, Mac OS X
```bash
$ export PATH=$PATH:`pwd`/third_party/gyp
```

- Windows
```cmd
> set PATH=%PATH%;%cd%\third_party\gyp
```

#### Cloning WebRTC

Retrieve WebRTC

```bash
$ git submodule init third_party/webrtc
$ git submodule update third_party/webrtc
```

### Windows, Git and Symbolic Links

This repository is using a lot of symbolic links, which are, for now, required
to build correctly with WebRTC. If you are running Windows and if your Git client doesn't support symbolic
links (Msysgit doesn't), you will have to use [this wonderful script](http://stackoverflow.com/a/16754068) inside
a GNU Shell, such as Git Bash, MSys or Cygwin.

#### Install the symlink script

Run a shell

```cmd
> sh
```

Copy and paste these lines

```bash
git config --global alias.rm-symlink '!__git_rm_symlink(){
    git checkout -- "$1"
    link=$(echo "$1")
    POS=$'\''/'\''
    DOS=$'\''\\\\'\''
    doslink=${link//$POS/$DOS}
    dest=$(dirname "$link")/$(cat "$link")
    dosdest=${dest//$POS/$DOS}
    if [ -f "$dest" ]; then
        rm -f "$link"
        cmd //C mklink //H "$doslink" "$dosdest"
    elif [ -d "$dest" ]; then
        rm -f "$link"
        cmd //C mklink //J "$doslink" "$dosdest"
    else
        echo "ERROR: Something went wrong when processing $1 . . ."
        echo "       $dest may not actually exist as a valid target."
    fi
}; __git_rm_symlink "$1"'

git config --global alias.rm-symlinks '!__git_rm_symlinks(){
    for symlink in $(git ls-files -s | egrep "^120000" | cut -f2); do
        git rm-symlink "$symlink"
        git update-index --assume-unchanged "$symlink"
    done
}; __git_rm_symlinks'

git config --global alias.checkout-symlinks '!__git_checkout_symlinks(){
    POS=$'\''/'\''
    DOS=$'\''\\\\'\''
    for symlink in $(git ls-files -s | egrep "^120000" | cut -f2); do
        git update-index --no-assume-unchanged "$symlink"
        dossymlink=${symlink//$POS/$DOS}
        cmd //C rmdir //Q "$dossymlink" 2>/dev/null
        git  checkout -- "$symlink"
        echo "Restored git symlink $symlink <<===>> $(cat $symlink)"
    done
}; __git_checkout_symlinks'
```

Then run the following command to generate the Windows shortcuts, from the
same shell :

```bash
$ git rm-symlinks
$ git submodule foreach --recursive git rm-symlinks
```

You will have to revert the shortcuts to their initial state before retrieving
the latest commits from the repository :

```bash
$ git checkout-symlinks
$ git submodule foreach --recursive git checkout-symlinks
```

It might display three failures, you shouldn't worry about it.

### Compiling

#### Compiling WebRTC

Get inside the WebRTC repository :

```bash
$ cd third_party/webrtc
```

Linux and Mac OS X users must retrieve another clang binary with the following command :

```bash
$ ./tools/clang/scripts/update.sh
```

Generate the build scripts and run ninja, Windows users **MUST** run these commands from their Windows CMD Prompt and not from a GNU Shell :

```bash
$ python webrtc/build/gyp_webrtc.py
$ ninja -C out/Release
```

#### Compiling libpeeracle

Simply go back to the libpeeracle repository and generate the build scripts

```bash
$ cd ../..
$ gyp build.gyp -f ninja -Dconfiguration=Release --no-circular-check --check -Ithird_party/webrtc/webrtc/build/common.gypi -Ithird_party/webrtc/webrtc/supplement.gypi --depth=.
```

If you don't like ninja, you can replace `-f ninja` by one of the following :
- `-f make` - Unix Makefile, then simply run `$ make`
- `-f msvs` - Visual Studio solution, then open `build.sln`
- `-f xcode` - XCode

Otherwise, just run

```bash
$ ninja -C out/Release
```
