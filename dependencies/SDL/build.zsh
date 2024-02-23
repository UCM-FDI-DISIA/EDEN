#!/bin/zsh

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de SDL que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de SDL

COMPILEDIR=../../src
BUILDDIR=./build
FILE=chkbuild.EDENBUILD
SDLBUILDVER=1.0
COMPILE=1

if test -f "$FILE"
then
    CHKBUILDVER=$(<$FILE)
    if [[ $SDLBUILDVER == $CHKBUILDVER ]]
    then
        COMPILE=0
    fi
else
    echo $SDLBUILDVER >$FILE
fi

if [[ $COMPILE == 1 ]]
then
    # Creamos la carpeta en la ruta de BUILDDIR
    mkdir $BUILDDIR
    cd $BUILDDIR

    architecture=$(uname -m)
    mkdir $architecture
    cd $architecture

    # Generamos con CMake a partir de la carpeta con el Src de SDL la solución de XCode con las tags correspondientes
    cmake -G "Xcode" -DCMAKE_OSX_ARCHITECTURES="$architecture" $COMPILEDIR

    # Compilamos SDL tanto en Debug como en Release
    xcodebuild -project SDL2.xcodeproj -configuration Debug
    xcodebuild -project SDL2.xcodeproj -configuration Release

    cd ../..

    echo SDL compilado
else
    echo ULTIMA VERSION DE SDL DETECTADA, no es necesario compilar
fi
