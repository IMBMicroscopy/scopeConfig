@ECHO OFF

echo Please Wait Whilst the System is Configured...

REM turn on power to scope and accessories via relay control unit
cd "C:\ScopeConfig\Relay_executables\"
Relay_Control.exe p com3

REM wait until system has powered up
PING 1.1.1.1 -n 13 -w 1000 >NUL


IF EXIST "c:\ScopeConfig\userList\NIS_%username%.txt" GOTO OLDUSER

cd "C:\Program Files\NIS-Elements\"
utl_exportsettings.exe -u la.admin -in "c:\ScopeConfig\NIS_Settings\NIS-Settings.bin"
@echo NIS settings enabled > "c:\ScopeConfig\userList\NIS_%username%.txt"
cd "c:\Windows\System32"
XCOPY "c:\ScopeConfig\NIS_Templates\Jobs" "D:\DATA\%username%\Jobs" /Q /E /I /R /Y
REM XCOPY "C:\ScopeConfig\NIS_Templates\Jobs\jobs.dat-shm" "D:\DATA\%username%\Jobs" /Q /E /I /R /Y
REM XCOPY "C:\ScopeConfig\NIS_Templates\Jobs\jobs.dat-wal" "D:\DATA\%username%\Jobs" /Q /E /I /R /Y
XCOPY "C:\ScopeConfig\NIS_Templates\Modified_Jobs\Modified\HCA" "C:\Program Files\NIS-Elements\JOBTemplates\HCA" /Q /E /I /R /Y
XCOPY "C:\ScopeConfig\NIS_Templates\Modified_Jobs\Modified\ND" "C:\Program Files\NIS-Elements\JOBTemplates\ND" /Q /E /I /R /Y

SET Path=[User]
SET Path1=File=
SET Path2=ND=
SET Path3=Jobs=
SET Path5=D:\DATA\%username%
SET Path6=\ND\Experiment
SET Path7=\Jobs\jobs.dat
SET Path9=c:\ScopeConfig\userList\currentuser.txt

@echo %Path% > %Path9%
@echo %Path1%%Path5% >> %Path9%
@echo %Path2%%Path5%%Path6% >> %Path9%
@echo %Path3%%Path5%%Path7% >> %Path9%

cd "C:\Program Files\NIS-Elements\"
START nis_ar.exe -m "C:\Program Files\NIS-Elements\Macros\startupNewUser.mac"
GOTO END

:OLDUSER
cd "C:\Program Files\NIS-Elements\"
START nis_ar.exe -m "C:\Program Files\NIS-Elements\Macros\startup.mac"

:END
EXIT