set "ProjectDir=%1"
set "Configuration=%2"
set "Platform=%3"
set "OutputDir=bin\%Platform%\%Configuration%"

cd %ProjectDir%

(robocopy ..\Celeste\Celeste\bin\%Platform%\%Configuration%\ %OutputDir% /E /IS /IT /XO) & exit 0