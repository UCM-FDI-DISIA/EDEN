@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de OGRE que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de OGRE
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de OGRE una vez se compile todo
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\..\bin
set OGREBUILDVER=1.4
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%OGREBUILDVER%" (
        set COMPILE=0
    ) else (
        del /q %BUILDDIR%
        echo %OGREBUILDVER%>chkbuild.EDENBUILD
    )
) else (
    del /q %BUILDDIR%
    echo %OGREBUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE OGRE
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
    cmake -A %PLATFORM% -DOGRE_BUILD_COMPONENT_BULLET:BOOL=0 -DOGRE_BUILD_COMPONENT_BITES:BOOL=0 -DOGRE_BUILD_PLUGIN_ASSIMP:BOOL=0 -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL=0 -DOGRE_BUILD_SAMPLES:BOOL=0 -DOGRE_INSTALL_SAMPLES:BOOL=0 -DOGRE_BUILD_TOOLS:BOOL=0 -DOGRE_INSTALL_TOOLS:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_D3D11:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_D3D9:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_GLES2:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_TINY:BOOL=0 -DOGRE_BUILD_RENDERSYSTEM_VULKAN:BOOL=0 -DOGRE_BUILD_PLUGIN_BSP:BOOL=0 -DOGRE_BUILD_PLUGIN_PCZ:BOOL=0 -DOGRE_BUILD_PLUGIN_OCTREE:BOOL=0 %COMPILEDIR%
    :: Compilamos OGRE tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    msbuild "OGRE.sln" /p:configuration=Debug /p:Platform=x64
    msbuild "OGRE.sln" /p:configuration=Release /p:Platform=x64
    :: Movemos las DLLs de OGRE generadas a la carpeta con ruta DLLFOLDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.
    for %%i in (".\bin\debug\*.dll") do (
        XCOPY /y /s "%%i" %DLLFOLDERS%
    )
    for %%j in (".\bin\release\*.dll") do (
        XCOPY /y /s "%%j" %DLLFOLDERS%
    )
    XCOPY /y /s .\bin\release\plugins.cfg %DLLFOLDERS%
    cd ..\..
    echo OGRE compilado
) else (
    echo ULTIMA VERSION DE OGRE DETECTADA, no es necesario compilar
)