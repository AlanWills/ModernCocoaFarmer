set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

rem Debugging
rem echo %OutputDir% > log.txt

cd %OutputDir%

(robocopy ..\..\..\..\ModernCocoaFarmerLibrary\bin\%Platform%\%Configuration%\ .\ /IS /IT /XO) ^&
(robocopy ..\..\..\..\CelesteEngine\CelesteEngine\bin\%Platform%\%Configuration%\ .\ /IS /IT /XO) ^&
(robocopy ..\..\..\..\CelesteEngine\BindingsGenerator\bin\%Platform%\%Configuration%\ .\ /IS /IT /XO) ^& exit 0