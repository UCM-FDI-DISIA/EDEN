@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de Bullet que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de Bullet
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set BULLETBUILDVER=1.4
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%BULLETBUILDVER%" (
        set COMPILE=0
    ) else (
        del /q %BUILDDIR%
        echo %BULLETBUILDVER%>chkbuild.EDENBUILD
    )
) else (
    del /q %BUILDDIR%
    echo %BULLETBUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE BULLET
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
    :: Generamos con CMake a partir de la carpeta con el Src de Bullet la solución de VSC++ con las tags correspondientes
    cmake -A %PLATFORM% -DBUILD_BULLET2_DEMOS:BOOL=0 -DBUILD_EXTRAS:BOOL=0 -DBUILD_ENET:BOOL=0 -DBUILD_CPU_DEMOS:BOOL=0 -DBUILD_CONVEX_DECOMPOSITION_EXTRA:BOOL=0 -DBUILD_CLSOCKET:BOOL=0 -DBUILD_BULLET_ROBOTICS_GUI_EXTRA:BOOL=0 -DBUILD_BULLET_ROBOTICS_EXTRA:BOOL=0 -DBUILD_GIMPACTUTILS_EXTRA:BOOL=0 -DBUILD_HACD_EXTRA:BOOL=0 -DBUILD_INVERSE_DYNAMIC_EXTRA:BOOL=0 -DBUILDOBJ2SDF_EXTRA:BOOL=0 -DBULLET2_MULTITHREADING:BOOL=0 -DBUILD_SHARED_LIBS:BOOL=0 -DBUILD_UNIT_TESTS=0 -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1 %COMPILEDIR%
    :: Compilamos Bullet tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug /maxcpucount
    msbuild "BULLET_PHYSICS.sln" /p:configuration=Release /maxcpucount
    :: En teoría Bullet no tiene .dll que mover a la carpeta donde se generan los .exe del motor
    cd ..\..
    echo Bullet compilado
) else (
    echo ULTIMA VERSION DE BULLET DETECTADA, no es necesario compilar
)