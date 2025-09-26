Echo off

RMDIR /S /Q "C:\Users\%username%\Documents\Fusion User Data"
Robocopy "c:\ScopeConfig\Settings\Fusion User Data" "C:\Users\%username%\Documents\Fusion User Data" /e
mkdir "D:\Data\%username%"

#REGEDIT.EXE  /S c:\ScopeConfig\ImarisSettings.reg

EXIT