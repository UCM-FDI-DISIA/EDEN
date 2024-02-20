@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de SDL que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de SDL
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de SDL una vez se compile todo
set COMPILEDIR=..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\bin

:: Creamos la carpeta en la ruta de BUILDDIR
mkdir %BUILDDIR%
cd %BUILDDIR%

:: Generamos con CMake a partir de la carpeta con el Src de SDL la solución de VSC++ con las tags correspondientes
cmake %COMPILEDIR%

:: Compilamos SDL tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
msbuild "SDL2.sln" /p:configuration=Debug
msbuild "SDL2.sln" /p:configuration=Release

:: Movemos las DLLs de SDL generadas a la carpeta con ruta DLLFOLDERS
:: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
:: /s copia directorios y subdirectorios, a menos que estén vacíos.

XCOPY /y /s .\Debug\SDL2d.dll %DLLFOLDERS%
XCOPY /y /s .\Release\SDL2.dll %DLLFOLDERS%

cd ..
echo SDL compilado