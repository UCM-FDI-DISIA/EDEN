@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de SDL que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de SDL
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de SDL una vez se compile todo
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\..\bin
set SDLBUILDVER=1.1
set COMPILE=1
set PLATFORM=x64

cd ..\SDL\src\include
set SDL2_INCLUDE_DIR=%CD%
cd ..\..\..\SDL_image

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
    echo INICIANDO LA COMPILACION DE SDL_image
    :: Creamos la carpeta en la ruta de BUILDDIR
    mkdir %BUILDDIR%
    cd %BUILDDIR%
    if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
        set ARCHDIR=x64
        mkdir !ARCHDIR!
        cd !ARCHDIR!
    ) else (
        if "%PROCESSOR_ARCHITECTURE%"=="x86" (
            set ARCHDIR=Win32
            mkdir !ARCHDIR!
            cd !ARCHDIR!
            set PLATFORM=!ARCHDIR!
        )
    )

    cd ..\..\..\SDL\build\!ARCHDIR!\Debug
    set SDL2_DEBUG_LIBRARY=!CD!\SDL2d.lib
    cd ..\Release
    set SDL2_RELEASE_LIBRARY=!CD!\SDL2.lib
    cd ..\..\..\..\SDL_image\build\!ARCHDIR!
    :: Generamos con CMake a partir de la carpeta con el Src de SDL la solución de VSC++ con las tags correspondientes
    :: Primero lo generamos para debug
    cmake -A %PLATFORM% -DSDL2_INCLUDE_DIR:PATH="%SDL2_INCLUDE_DIR%" -DSDL2_LIBRARY:FILEPATH="!SDL2_DEBUG_LIBRARY!" -DSDL2IMAGE_INSTALL:BOOL=0 %COMPILEDIR%
    msbuild "SDL2_image.sln" /p:configuration=Debug
    cmake -A %PLATFORM% -DSDL2_INCLUDE_DIR:PATH="%SDL2_INCLUDE_DIR%" -DSDL2_LIBRARY:FILEPATH="!SDL2_RELEASE_LIBRARY!" -DSDL2IMAGE_INSTALL:BOOL=0 %COMPILEDIR%
    msbuild "SDL2_image.sln" /p:configuration=Release
    :: Movemos las DLLs de SDL generadas a la carpeta con ruta DLLFOLFDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.
    XCOPY /y /s .\Debug\SDL2_imaged.dll %DLLFOLDERS%
    XCOPY /y /s .\Release\SDL2_image.dll %DLLFOLDERS%
    cd ..\..
    echo SDL_image compilado
) else (
    echo ULTIMA VERSION DE SDL_image DETECTADA, no es necesario compilar
)