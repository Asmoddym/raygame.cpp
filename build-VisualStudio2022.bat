cd build
premake5.exe vs2022 || pause
premake5.exe export-compile-commands
cd ../
copy compile_commands/debug_x86.json compile_commands.json

set configuration=%1

del Bin\%configuration%\raygame.exe

echo CONFIGURATION: %configuration%

call "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" /property:Configuration=%configuration% /p:CONFIGURATION=%configuration%

call Bin\%configuration%\raygame.exe

