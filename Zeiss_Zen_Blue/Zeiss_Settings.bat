@ECHO OFF
IF EXIST "c:\ScopeConfig\userList\Zeiss_%username%.txt" GOTO OLDUSER

xcopy "C:\ScopeConfig\DefaultSettings\Roaming" "C:\Users\%username%\AppData\Roaming\" /Y /E /I /H 
xcopy "C:\ScopeConfig\DefaultSettings\Carl Zeiss" "C:\Users\%username%\Documents\Carl Zeiss" /Y /E /I /H 

@echo Zen settings enabled > "c:\ScopeConfig\userList\Zeiss_%username%.txt"

:OLDUSER
cd "C:\Program Files\Carl Zeiss\ZEN 2\ZEN 2 (blue edition)\"
start "" ZEN.exe

EXIT


