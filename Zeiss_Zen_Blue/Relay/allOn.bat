@ECHO OFF

ECHO Please wait for the hardware to power on, then start the microscope stand

cd "C:\ScopeConfig\Relay\" > NUL
START /B scopeOn.exe > NUL
PING localhost -n 3 > NUL
START /B lampOn.exe > NUL

echo Press any key to continue
TIMEOUT /T 10