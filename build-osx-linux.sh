#!/usr/bin/env sh

RULE="gmake2"
TYPE="Debug"

rm -rf bin/$TYPE/raygame

pushd build
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx $RULE || ./premake5 $RULE
popd
make

./bin/$TYPE/raygame
