#!/bin/zsh

#Limpiamos la pantalla para que se muestren los mensajes
clear

#Nos guardamos el nombre del archivo que vamos a compilar por cada dependencia (por defecto, los vamos a llamar build.zsh)
SH=build.zsh

cd ./dependencies/

cd ./Ogre/
./$SH

cd ../SDL/
./$SH

cd ../Bullet/
./$SH
