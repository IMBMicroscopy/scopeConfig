@Echo off

IF EXIST "c:\ScopeConfig\userList\Leica_%username%.txt" GOTO OLDUSER

c:\Windows\System32\xcopy.exe "c:\ScopeConfig\DefaultSettings\Roaming" "c:\Users\%username%\AppData\Roaming\" /e /i /h /y
c:\Windows\System32\xcopy.exe "c:\ScopeConfig\DefaultSettings\Local" "c:\Users\%username%\AppData\Local\" /e /i /h /y

@echo Leica settings enabled > "c:\ScopeConfig\userList\Leica_%username%.txt"

:OLDUSER


EXIT

