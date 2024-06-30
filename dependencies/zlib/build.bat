@echo off
:: Especificamos las direcciones que vamos a usar
:: COMPILEDIR es la dirección donde se encuentra el source de zlib que vamos a compilar
:: BUILDDIR es la dirección en la que vamos a volcar la build de zlib
:: DLLFOLDERS es la carpeta donde vamos a meter las DLL de zlib una vez se compile todo
SETLOCAL ENABLEDELAYEDEXPANSION
set COMPILEDIR=..\..\src
set BUILDDIR=.\build
set DLLFOLDERS=.\..\..\..\..\bin
set ZLIBBUILDVER=1.3.1
set COMPILE=1
set PLATFORM=x64

if exist chkbuild.EDENBUILD (
    set /p CHKBUILDVER=<chkbuild.EDENBUILD
    if "!CHKBUILDVER!"=="%ZLIBBUILDVER%" (
        set COMPILE=0
    ) else (
        del /q %BUILDDIR%
        echo %ZLIBBUILDVER%>chkbuild.EDENBUILD
    )
) else (
    del /q %BUILDDIR%
    echo %ZLIBBUILDVER%>chkbuild.EDENBUILD
)

if !COMPILE! equ 1 (
    echo INICIANDO LA COMPILACION DE ZLIB
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
    :: Generamos con CMake a partir de la carpeta con el src de zlib la solución de VSC++ con las tags correspondientes
    cmake -A %PLATFORM% -DZLIB_BUILD_EXAMPLES:BOOL=0 %COMPILEDIR%
    :: Compilamos OGRE tanto en Debug como en Release (solo hemos creado para x64, no tenemos que preocuparnos por Win32)
    msbuild "zlib.sln" /p:configuration=Debug /p:Platform=x64
    msbuild "zlib.sln" /p:configuration=Release /p:Platform=x64
    :: Movemos las DLLs de zlib generadas a la carpeta con ruta DLLFOLDERS
    :: /y suprime la solicitud para confirmar que desea sobrescribir un archivo de destino existente.
    :: /s copia directorios y subdirectorios, a menos que estén vacíos.
    for %%i in (".\Debug\*.dll") do (
        XCOPY /y /s "%%i" %DLLFOLDERS%
    )
    for %%j in (".\Release\*.dll") do (
       XCOPY /y /s "%%j" %DLLFOLDERS%
    )
    cd ..\..
    echo zlib compilado
) else (
    echo ULTIMA VERSION DE ZLIB DETECTADA, no es necesario compilar
)