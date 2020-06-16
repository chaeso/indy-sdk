#!/bin/sh

# Setup
rustup target add aarch64-apple-ios armv7-apple-ios armv7s-apple-ios i386-apple-ios x86_64-apple-ios
cargo install cargo-lipo
brew install libsodium
brew install zeromq
brew install openssl

# Build
export PKG_CONFIG_ALLOW_CROSS=1
export CARGO_INCREMENTAL=1

# ls -alh export OPENSSL_DIR=/usr/local/Cellar/openssl/ 
export OPENSSL_DIR=/usr/local/Cellar/openssl/1.0.2s
export LIBINDY_POD_VERSION=0.0.1

cargo lipo #--release



cp target/aarch64-apple-ios/debug/libindy.a tester/ios/ios-tester/
