#!/bin/zsh

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de Lua que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de Lua

COMPILEDIR=../../src
BUILDDIR=./build
FILE=chkbuild.EDENBUILD
LUABUILDVER=1.0
COMPILE=1

if test -f "$FILE"
then
    CHKBUILDVER=$(<$FILE)
    if [[ $LUABUILDVER == $CHKBUILDVER ]]
    then
        COMPILE=0
    else
        rm -rf $BUILDDIR
        echo $LUABUILDVER >$FILE
    fi
else
    rm -rf $BUILDDIR
    echo $LUABUILDVER >$FILE
fi

if [[ $COMPILE == 1 ]]
then
    # Creamos la carpeta en la ruta de BUILDDIR
    mkdir $BUILDDIR
    cd $BUILDDIR

    architecture=$(uname -m)
    mkdir $architecture
    cd $architecture

    # Generamos con CMake a partir de la carpeta con el Src de LUA la solución de XCode con las tags correspondientes
    cmake -G "Xcode" -DCMAKE_OSX_ARCHITECTURES="$architecture" $COMPILEDIR

    # Compilamos LUA tanto en Debug como en Release
    xcodebuild -project LUA_C.xcodeproj -configuration Debug
    xcodebuild -project LUA_C.xcodeproj -configuration Release

    cd ../..

    echo LUA compilado
else
    echo ULTIMA VERSION DE LUA DETECTADA, no es necesario compilar
fi
