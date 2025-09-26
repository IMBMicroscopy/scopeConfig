@ECHO OFF

xcopy "C:\ScopeConfig\DefaultSettings\Roaming" "C:\Users\%username%\AppData\Roaming\" /Y /E /I /H 
xcopy "C:\ScopeConfig\DefaultSettings\Carl Zeiss" "C:\Users\%username%\Documents\Carl Zeiss" /Y /E /I /H 

@echo Zen settings enabled > "c:\ScopeConfig\userList\Zeiss_%username%.txt"

EXIT

