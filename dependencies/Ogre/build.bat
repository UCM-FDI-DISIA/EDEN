@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de OGRE que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de OGRE
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de OGRE una vez se compile todo
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\..\bin
set OGREBUILDVER=1.0
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "%CHKBUILDVER%"=="%OGREBUILDVER%" (
        set COMPILE=0
    )
) else (
    echo %OGREBUILDVER%>chkbuild.EDENBUILD
)

if %COMPILE%==1 (
    echo INICIANDO LA COMPILACIÓN DE OGRE
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

    :: Generamos con CMake a partir de la carpeta con el Src de OGRE la solución de VSC++ con las tags correspondientes
    cmake -A %PLATFORM% -DOGRE_BUILD_COMPONENT_BULLET:BOOL=0 -DOGRE_BUILD_COMPONENT_BITES:BOOL=0 %COMPILEDIR%

    :: Compilamos OGRE tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    msbuild "OGRE.sln" /p:configuration=Debug /maxcpucount
    msbuild "OGRE.sln" /p:configuration=Release /maxcpucount

    :: Movemos las DLLs de OGRE generadas a la carpeta con ruta DLLFOLDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.

    XCOPY /y /s .\bin\debug\OgreMain_d.dll %DLLFOLDERS%
    XCOPY /y /s .\bin\release\OgreMain.dll %DLLFOLDERS%

    cd ..\..

    echo OGRE compilado
) else (
    echo ULTIMA VERSION DE OGRE DETECTADA, no es necesario compilar
)
