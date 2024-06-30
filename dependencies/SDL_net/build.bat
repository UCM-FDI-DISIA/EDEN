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
    echo INICIANDO LA COMPILACION DE SDL
    :: Creamos la carpeta en la ruta de BUILDDIR
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
    :: Generamos con CMake a partir de la carpeta con el src de SDL_net la solución de VSC++ con las tags correspondientes
    :: Compilamos SDL tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    cmake -A %PLATFORM% -DSDL2_DIR="../../../SDL/Src/" -DSDL2_LIBRARY="../../../SDL/build/%PLATFORM%/Debug/SDL2d.lib" -DSDL2_INCLUDE_DIR="../../../SDL/Src/include/" %COMPILEDIR%
    msbuild "SDL2_net.sln" /p:configuration=Debug /p:Platform=x64
    cmake -A %PLATFORM% -DSDL2_DIR="../../../SDL/Src/" -DSDL2_LIBRARY="../../../SDL/build/%PLATFORM%/Release/SDL2.lib" -DSDL2_INCLUDE_DIR="../../../SDL/Src/include/" %COMPILEDIR%
    msbuild "SDL2_net.sln" /p:configuration=Release /p:Platform=x64
    :: Movemos las DLLs de SDL_net generadas a la carpeta con ruta DLLFOLDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.
    XCOPY /y /s .\Debug\SDL2_netd.dll %DLLFOLDERS%
    XCOPY /y /s .\Release\SDL2_net.dll %DLLFOLDERS%
    cd ..\..
    echo SDL_net compilado
) else (
    echo ULTIMA VERSION DE SDL DETECTADA, no es necesario compilar
)