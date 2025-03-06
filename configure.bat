d:
cd "D:\Programas\LMMS Compiled\lmms"
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH=D:/Programas/Qt/5.15.2/msvc2019_64 -DQT_32_PREFIX=D:/Programas/Qt/5.15.2/msvc2019 -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake

pause