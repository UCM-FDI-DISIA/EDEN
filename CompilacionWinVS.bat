@echo off

:: Limpiamos la pantalla para que se muestren los mensajes
cls

:: Nos guardamos el nombre del archivo que vamos a compilar por cada dependencia (por defecto, los vamos a llamar build.bat)
set BAT=build.bat

cd .\dependencies\

cd .\Ogre\
call %BAT%

cd ..\SDL\
call %BAT%

cd ..\Bullet\
call %BAT%

cd ..\Lua\
call %BAT%

cd ..\irrKlang\
call %BAT%

cd ..\SDL_net\
call %BAT%

cd ..\zlib\
call %BAT%

cd ..\..

call CompilarMotor.bat
