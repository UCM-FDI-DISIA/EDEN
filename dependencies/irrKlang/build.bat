@echo off
set DLLFOLDERS=.\..\..\bin

for %%i in (".\build\x64\*.dll") do (
    XCOPY /y /s "%%i" %DLLFOLDERS%
)