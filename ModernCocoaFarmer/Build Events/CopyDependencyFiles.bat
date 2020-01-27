set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"
set "ResourcesDir=%4"

rem Debugging
rem echo %OutputDir% > log.txt
rem echo %OutputDir%..\..\..\..\3rdParty\DLL >> log.txt

cd %OutputDir%

(robocopy ..\..\..\..\ModernCocoaFarmerLibrary\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\Resources %ResourcesDir% /E /IS /IT /XO) & exit 0