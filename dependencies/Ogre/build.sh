#!/bin/bash

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de OGRE que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de OGRE

COMPILEDIR=../src
BUILDDIR=./build
SOFOLDERS=./../../../bin

# Creamos la carpeta en la ruta de BUILDDIR
mkdir $BUILDDIR
cd $BUILDDIR

# Generamos con CMake a partir de la carpeta con el Src de OGRE la solución de XCode con las tags correspondientes
cmake -G "Xcode" -DOGRE_BUILD_COMPONENT_BULLET:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_LIBS_AS_FRAMEWORKS:BOOL="0" $COMPILEDIR

# Compilamos OGRE tanto en Debug como en Release
xcodebuild -project OGRE.xcodeproj -configuration Debug
xcodebuild -project OGRE.xcodeproj -configuration Release

cd ..

echo OGRE compilado
