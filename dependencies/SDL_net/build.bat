@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\..\bin
set SDLBUILDVER=2.2.0
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%SDLBUILDVER%" (
        set COMPILE=0
    ) else (
        del /q %BUILDDIR%
        echo %SDLBUILDVER%>chkbuild.EDENBUILD
    )
) else (
    del /q %BUILDDIR%
    echo %SDLBUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE SDL_NET
    mkdir %BUILDDIR%
    cd %BUILDDIR%
    if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
        mkdir x64
        cd x64
    ) else (
        if "%PROCESSOR_ARCHITECTURE%"=="x86" (
            mkdir Win32
            cd Win32
            set PLATFORM=Win32
        )
    )
    cmake -A %PLATFORM% -DSDL2_DIR="../../../SDL/Src/" -DSDL2_LIBRARY="../../../SDL/build/%PLATFORM%/Debug/SDL2d.lib" -DSDL2_INCLUDE_DIR="../../../SDL/Src/include/" %COMPILEDIR%
    msbuild "SDL2_net.sln" /p:configuration=Debug /p:Platform=x64
    cmake -A %PLATFORM% -DSDL2_DIR="../../../SDL/Src/" -DSDL2_LIBRARY="../../../SDL/build/%PLATFORM%/Release/SDL2.lib" -DSDL2_INCLUDE_DIR="../../../SDL/Src/include/" %COMPILEDIR%
    msbuild "SDL2_net.sln" /p:configuration=Release /p:Platform=x64
    XCOPY /y /s .\Debug\SDL2_netd.dll %DLLFOLDERS%
    XCOPY /y /s .\Release\SDL2_net.dll %DLLFOLDERS%
    cd ..\..
    echo SDL_net compilado
) else (
    echo ULTIMA VERSION DE SDL_NET DETECTADA, no es necesario compilar.
)