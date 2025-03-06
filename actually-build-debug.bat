c:
cd "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\"
call VsDevCmd.bat
d:
cd "D:\Programas\LMMS_compiled\lmms\build"
cmake --install . --config Debug --prefix=D:/Programas/LMMS-Compiled-Debug/
explorer.exe "D:\Programas\LMMS-Compiled-Debug\"
pause