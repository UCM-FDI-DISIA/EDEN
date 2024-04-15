@echo off

:: Script para la compilación del motor EDEN

msbuild "EDEN.sln" /p:configuration=Debug /p:Platform=x64
msbuild "EDEN.sln" /p:configuration=Release /p:Platform=x64