#!/bin/zsh

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de Bullet que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de Bullet

COMPILEDIR=../../src
BUILDDIR=./build
FILE=chkbuild.EDENBUILD
BULLETBUILDVER=1.0
COMPILE=1

if test -f "$FILE"
then
    CHKBUILDVER=$(<$FILE)
    if [[ $BULLETBUILDVER == $CHKBUILDVER ]]
    then
        COMPILE=0
    fi
else
    echo $BULLETBUILDVER >$FILE
fi

if [[ $COMPILE == 1 ]]
then
    # Creamos la carpeta en la ruta de BUILDDIR
    mkdir $BUILDDIR
    cd $BUILDDIR

    architecture=$(uname -m)
    mkdir $architecture
    cd $architecture

    # Generamos con CMake a partir de la carpeta con el Src de BULLET la solución de XCode con las tags correspondientes
    cmake -G "Xcode" -DCMAKE_OSX_ARCHITECTURES="$architecture" $COMPILEDIR

    # Compilamos BULLET tanto en Debug como en Release
    xcodebuild -project BULLET_PHYSICS.xcodeproj -configuration Debug
    xcodebuild -project BULLET_PHYSICS.xcodeproj -configuration Release

    cd ..

    echo BULLET compilado
else
    echo ULTIMA VERSION DE BULLET DETECTADA, no es necesario compilar
fi
