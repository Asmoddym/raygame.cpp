#!/usr/bin/env sh



rm -rf bin/$TYPE/raygame
RULE="gmake2"
TYPE="Debug"

pushd build
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx $RULE || ./premake5 $RULE
popd
make
./bin/$TYPE/raygame
