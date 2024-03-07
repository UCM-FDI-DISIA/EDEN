@echo off
:: Ejecutar este .bat si se quiere compilar aunque ya se haya compilado.
set CHKBUILD=chkbuild.EDENBUILD
cls

for %%i in (".\bin\*.dll") do (
    del "%%i"
)
for %%j in (".\bin\*.cfg") do (
    del "%%j"
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

cd ..\FMOD\
del %CHKBUILD%
rd /s /q .\build\

cd ..\SDL_ttf\
del %CHKBUILD%
rd /s /q .\build\

cd ..\SDL_image\
del %CHKBUILD%
rd /s /q .\build\

call CompilacionWinVS.bat