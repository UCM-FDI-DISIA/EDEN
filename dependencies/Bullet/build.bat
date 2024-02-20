@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de Bullet que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de Bullet
set COMPILEDIR=..\src
set BUILDDIR=.\build

:: Creamos la carpeta en la ruta de BUILDDIR
mkdir %BUILDDIR%
cd %BUILDDIR%

:: Generamos con CMake a partir de la carpeta con el Src de Bullet la solución de VSC++ con las tags correspondientes
cmake %COMPILEDIR%

:: Compilamos Bullet tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug /maxcpucount
msbuild "BULLET_PHYSICS.sln" /p:configuration=Release /maxcpucount

:: En teoría Bullet no tiene .dll que mover a la carpeta donde se generan los .exe del motor

cd ..

echo Bullet compilado