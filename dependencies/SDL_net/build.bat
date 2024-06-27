@echo off
:: Especificamos las direcciones que vamos a usar
:: BUILDDIR es la dirección en la que vamos a volcar la build de SDL
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de SDL una vez se compile todo
SETLOCAL ENABLEDELAYEDEXPANSION
set BUILDDIR=.\lib
set DLLFOLDERS=.\..\..\..\..\bin
set SDLBUILDVER=1.1
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%SDLBUILDVER%" (
        set COMPILE=0
    ) else (
        echo %SDLBUILDVER%>chkbuild.EDENBUILD
    )
) else (
    echo %SDLBUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE SDL
    :: Movemos las DLLs de SDL generadas a la carpeta con ruta DLLFOLDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.
    XCOPY /y /s .\lib\%PLATFORM%\SDL2_net.dll %DLLFOLDERS%
    cd ..\..
    echo SDL compilado
) else (
    echo ULTIMA VERSION DE SDL DETECTADA, no es necesario compilar
)