set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

cd %OutputDir%

(robocopy ..\..\..\..\CelesteEngine\CelesteEngine\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) & exit 0