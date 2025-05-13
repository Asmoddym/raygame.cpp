#!/usr/bin/env sh

CONFIGURATION=$1

if [ -z "$CONFIGURATION" ]; then
  CONFIGURATION="Debug"
fi

rm -rf bin/$CONFIGURATION/raygame

pushd build
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx gmake2 || ./premake5 gmake2
popd

make

pushd build
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx export-compile-commands || ./premake5 export-compile-commands
popd

cp ./compile_commands/debug_x64.json ./compile_commands.json

./bin/$CONFIGURATION/raygame
