#!/usr/bin/env sh

rm -rf bin/$TYPE/raygame
RULE="gmake2"
TYPE="Debug"

pushd build
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx $RULE || ./premake5 $RULE
[[ $OSTYPE == 'darwin'* ]] && ./premake5.osx export-compile-commands || ./premake5 export-compile-commands
popd
cp ./compile_commands/debug_x86.json ./compile_commands.json
make
./bin/$TYPE/raygame
