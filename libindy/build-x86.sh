#!/bin/sh

cargo build  # -release
#cp target/x86_64-apple-ios/debug/libindy.a tester/x86
cp target/debug/libindy.* ../samples/python/src
