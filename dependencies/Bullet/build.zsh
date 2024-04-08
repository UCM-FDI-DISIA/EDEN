#!/bin/zsh

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de Bullet que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de Bullet

COMPILEDIR=../../src
BUILDDIR=./build
FILE=chkbuild.EDENBUILD
BULLETBUILDVER=1.2
COMPILE=1

if test -f "$FILE"
then
    CHKBUILDVER=$(<$FILE)
    if [[ $BULLETBUILDVER == "$CHKBUILDVER" ]]
    then
        COMPILE=0
    else
        rm -rf $BUILDDIR
        echo $BULLETBUILDVER >$FILE
    fi
else
    rm -rf $BUILDDIR
    echo $BULLETBUILDVER >$FILE
fi

if [[ $COMPILE == 1 ]]
then
    # Creamos la carpeta en la ruta de BUILDDIR
    mkdir $BUILDDIR
    cd "$BUILDDIR"

    architecture=$(uname -m)
    mkdir "$architecture"
    cd "$architecture"

    # Generamos con CMake a partir de la carpeta con el Src de BULLET la solución de XCode con las tags correspondientes
    cmake -G "Xcode" -DCMAKE_OSX_ARCHITECTURES="$architecture" -DBUILD_BULLET2_DEMOS:BOOL=0 -DBUILD_EXTRAS:BOOL=0 -DBUILD_ENET:BOOL=0 -DBUILD_CPU_DEMOS:BOOL=0 -DBUILD_CONVEX_DECOMPOSITION_EXTRA:BOOL=0 -DBUILD_CLSOCKET:BOOL=0 -DBUILD_BULLET_ROBOTICS_GUI_EXTRA:BOOL=0 -DBUILD_BULLET_ROBOTICS_EXTRA:BOOL=0 -DBUILD_GIMPACTUTILS_EXTRA:BOOL=0 -DBUILD_HACD_EXTRA:BOOL=0 -DBUILD_INVERSE_DYNAMIC_EXTRA:BOOL=0 -DBUILDOBJ2SDF_EXTRA:BOOL=0 -DBULLET2_MULTITHREADING:BOOL=0 -DBUILD_UNIT_TESTS=0 $COMPILEDIR

    # Compilamos BULLET tanto en Debug como en Release
    xcodebuild -project BULLET_PHYSICS.xcodeproj -configuration Debug
    xcodebuild -project BULLET_PHYSICS.xcodeproj -configuration Release

    cd ../..

    echo BULLET compilado
else
    echo ULTIMA VERSION DE BULLET DETECTADA, no es necesario compilar
fi