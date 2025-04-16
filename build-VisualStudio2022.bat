cd build
premake5.exe vs2022 || pause
cd ../

set configuration=Debug

del Bin\%configuration%\raygame.exe
call "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" /property:Configuration=%configuration%
call Bin\Debug\raygame.exe
