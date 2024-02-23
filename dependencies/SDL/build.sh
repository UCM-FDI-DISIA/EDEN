#!/bin/bash

# Especificamos las direcciones que vamos a usar
# COMPILEDIR es la dirección donde se encuentra el source de SDL que vamos a compilar
# BUILDDIR es la dirección en la que vamos a volcar la build de SDL

COMPILEDIR=../src
BUILDDIR=./build

# Creamos la carpeta en la ruta de BUILDDIR
mkdir $BUILDDIR
cd $BUILDDIR

# Generamos con CMake a partir de la carpeta con el Src de SDL la solución de XCode con las tags correspondientes
cmake -G "Xcode" $COMPILEDIR

# Compilamos SDL tanto en Debug como en Release
xcodebuild -project SDL2.xcodeproj -configuration Debug
xcodebuild -project SDL2.xcodeproj -configuration Release

cd ..

echo SDL compilado
