Echo off

IF EXIST "c:\ScopeConfig\userList\Zeiss_%username%.txt" GOTO OLDUSER

Robocopy "c:\ScopeConfig\Local" "C:\Users\%username%\AppData\Local" /e
Robocopy "C:\ScopeConfig\Roaming" "c:\Users\%username%\AppData\Roaming" /e

REGEDIT.EXE  /S c:\ScopeConfig\Zeiss_Settings.reg

@echo Zen settings enabled > "c:\ScopeConfig\userList\Zeiss_%username%.txt"

OLDUSER:

EXIT