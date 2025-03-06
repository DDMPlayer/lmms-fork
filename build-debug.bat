@echo off
cd build
cmake --build . --config "Debug" -j 8
cd ..
c:
cd "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\"
call VsDevCmd.bat
cd "C:\LMMS-Compiled\build"
cmake --install . --config Release --prefix=C:\LMMS-Compiled\build\
C:\LMMS-Compiled\build\lmms.exe
