@echo off
setlocal enabledelayedexpansion

rem Builds XDoku on Windows via CMake + Ninja + vcpkg. Requires VCPKG_ROOT set
rem and glfw3/libpqxx already installed for the x64-windows-static-md triplet.

if "%VCPKG_ROOT%"=="" (
    echo ERROR: VCPKG_ROOT is not set. Point it at your vcpkg checkout first, e.g.:
    echo   set VCPKG_ROOT=C:\vcpkg
    exit /b 1
)

if not exist "%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" (
    echo ERROR: "%VCPKG_ROOT%" doesn't look like a vcpkg checkout ^(vcpkg.cmake not found^).
    exit /b 1
)

rem vcvars64.bat overwrites VCPKG_ROOT with VS's own bundled vcpkg, so save it first.
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

rem Repo root is one level up from this script.
set "REPO_ROOT=%~dp0..\."

cmake -B "%REPO_ROOT%\build" -S "%REPO_ROOT%" -G Ninja -DCMAKE_TOOLCHAIN_FILE="%MY_VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static-md
if errorlevel 1 exit /b 1

cmake --build "%REPO_ROOT%\build"
if errorlevel 1 exit /b 1

echo.
echo Build succeeded: %REPO_ROOT%\build\XDoku.exe
