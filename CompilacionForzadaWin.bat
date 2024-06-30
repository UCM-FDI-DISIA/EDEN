@echo off
:: Ejecutar este .bat si se quiere compilar aunque ya se haya compilado.
set CHKBUILD=chkbuild.EDENBUILD
cls

for %%i in (".\bin\*.dll") do (
    del "%%i"
)

cd .\dependencies\

cd .\Ogre\
del %CHKBUILD%
rd /s /q .\build\

cd ..\SDL\
del %CHKBUILD%
rd /s /q .\build\

cd ..\Bullet\
del %CHKBUILD%
rd /s /q .\build\

cd ..\Lua\
del %CHKBUILD%
rd /s /q .\build\

cd ..\SDL_net\
del %CHKBUILD%
rd /s /q .\build\

cd ..\..

call CompilacionWinVS.bat