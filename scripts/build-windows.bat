@echo off
setlocal enabledelayedexpansion

rem Builds XDoku on Windows: finds a VS C++ toolset, imports its x64 dev environment,
rem then configures and builds via CMake + Ninja against a vcpkg toolchain.
rem
rem Prerequisite: set VCPKG_ROOT to your vcpkg checkout, and have already run
rem   vcpkg install glfw3:x64-windows-static-md libpqxx:x64-windows-static-md
rem (see README.md for why that specific triplet is required).

if "%VCPKG_ROOT%"=="" (
    echo ERROR: VCPKG_ROOT is not set. Point it at your vcpkg checkout first, e.g.:
    echo   set VCPKG_ROOT=C:\vcpkg
    exit /b 1
)

if not exist "%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" (
    echo ERROR: "%VCPKG_ROOT%" doesn't look like a vcpkg checkout ^(vcpkg.cmake not found^).
    exit /b 1
)

rem Capture this before importing the VS dev environment below: vcvars64.bat resets
rem VCPKG_ROOT to VS's own bundled vcpkg (VC\vcpkg), clobbering whatever the caller set.
set "MY_VCPKG_ROOT=%VCPKG_ROOT%"

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo ERROR: vswhere.exe not found. Is Visual Studio or the VS Build Tools installed?
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALL=%%i"
if "%VSINSTALL%"=="" (
    echo ERROR: No Visual Studio installation with the C++ ^(x86/x64^) build tools was found.
    exit /b 1
)

set "VCVARS=%VSINSTALL%\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
    echo ERROR: vcvars64.bat not found at "%VCVARS%"
    exit /b 1
)

call "%VCVARS%"
if errorlevel 1 exit /b 1

rem This script lives in scripts\, one level below the repo root that has CMakeLists.txt.
rem "%~dp0.." ends in a backslash, which escapes a following closing quote on Windows
rem command lines - "%~dp0..\." avoids that trap. Absolute -B/-S paths let this script be
rem invoked from any working directory.
set "REPO_ROOT=%~dp0..\."

cmake -B "%REPO_ROOT%\build" -S "%REPO_ROOT%" -G Ninja -DCMAKE_TOOLCHAIN_FILE="%MY_VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static-md
if errorlevel 1 exit /b 1

cmake --build "%REPO_ROOT%\build"
if errorlevel 1 exit /b 1

echo.
echo Build succeeded: %REPO_ROOT%\build\XDoku.exe
