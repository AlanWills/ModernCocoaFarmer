set "OutputDir=%1"
set "Platform=%2"

rem Debugging
rem echo %OutputDir% > log.txt
rem echo %OutputDir%..\..\..\..\3rdParty\DLL >> log.txt

cd %OutputDir%

(robocopy ..\..\..\..\CelesteEngine\CelesteEngine\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\Resources .\Resources /E /IS /IT /XO) & exit 0