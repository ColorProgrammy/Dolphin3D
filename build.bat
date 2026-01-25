@echo off
setlocal enabledelayedexpansion

title Dolphin3D Builder

echo Dolphin3D (v1.0) - Builder

cmake --version >nul 2>&1
if errorlevel 1 (
    color 04
    echo ERROR: CMake not found!
    echo.
    echo Please install CMake from:
    echo https://cmake.org/download/
    echo.
    echo Make sure CMake is in your PATH.
    pause
    exit /b 1
)

:menu
echo.
echo Build options:
echo 1) Build
echo 2) Clean everything and exit
echo.
set /p choice="Select [1-2]: "

if "%choice%"=="1" goto build
if "%choice%"=="2" goto clean_all
goto menu

:build
echo.
echo Starting build... (It may take a while)
echo.

if exist build (
    echo Removing old build directory...
    rmdir /S /Q build
)
if exist bin\Dolphin3D.exe (
    echo Removing old executable...
    del /Q bin\Dolphin3D.exe
)

if not exist bin mkdir bin
echo Build started: %date% %time% > bin\BuildLog.txt
echo ================================= >> bin\BuildLog.txt
echo. >> bin\BuildLog.txt

mkdir build
cd build

echo Configuring project...
cmake .. >> ..\bin\BuildLog.txt 2>&1
if errorlevel 1 (
    color 04
    echo ERROR: CMake configuration failed!
    cd ..
    goto error
)

echo Building project...
cmake --build . --config Release >> ..\bin\BuildLog.txt 2>&1
if errorlevel 1 (
    color 04
    echo ERROR: Build failed!
    cd ..
    goto error
)

cd ..

echo Copying executable...
if exist build\Release\Dolphin3D.exe (
    copy /Y build\Release\Dolphin3D.exe bin\ >nul
) 
if exist build\Dolphin3D.exe (
    copy /Y build\Dolphin3D.exe bin\ >nul
) 
if exist bin\Release\Dolphin3D.exe (
    copy /Y bin\Release\Dolphin3D.exe bin\ >nul
    rmdir /S /Q bin\Release 2>nul
)

if not exist bin\Dolphin3D.exe (
    color 04
    echo ERROR: Executable not found!
    goto error
)

color 02
echo Build successful!
echo.

if exist bin\Dolphin3D.exe (
    for %%F in ("bin\Dolphin3D.exe") do echo Executable: bin\Dolphin3D.exe [%%~zF bytes]
)

if exist build (
    echo Cleaning up...
    rmdir /S /Q build
)

echo.
echo Build completed at %time%
echo Log file: bin\BuildLog.txt
pause
exit /b 0

:error
echo.
color 04
echo ERROR: Build failed! Check bin\BuildLog.txt for details.

if exist build (
    rmdir /S /Q build
)

pause
exit /b 1

:clean_all
echo.
echo Cleaning everything...
if exist build rmdir /S /Q build
if exist bin\Dolphin3D.exe del /Q bin\Dolphin3D.exe
if exist bin\assets rmdir /S /Q bin\assets
if exist bin\BuildLog.txt del /Q bin\BuildLog.txt
if exist bin\Release rmdir /S /Q bin\Release
echo Cleanup completed.
pause
exit /b 0