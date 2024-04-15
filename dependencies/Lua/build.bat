@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de Lua que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de Lua
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set LUABUILDVER=1.1
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%LUABUILDVER%" (
        set COMPILE=0
    ) else (
        del /q %BUILDDIR%
        echo %LUABUILDVER%>chkbuild.EDENBUILD
    )
) else (
    del /q %BUILDDIR%
    echo %LUABUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE LUA
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
    :: Generamos con CMake a partir de la carpeta con el Src de Lua la solución de VSC++ con las tags correspondientes
    cmake -A %PLATFORM% %COMPILEDIR%
    :: Compilamos Lua tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    msbuild "LUA_C.sln" /p:configuration=Debug /p:Platform=x64
    msbuild "LUA_C.sln" /p:configuration=Release /p:Platform=x64
    :: En teoría Bullet no tiene .dll que mover a la carpeta donde se generan los .exe del motor
    cd ..\..
    echo Lua compilado
) else (
    echo ULTIMA VERSION DE LUA DETECTADA, no es necesario compilar
)