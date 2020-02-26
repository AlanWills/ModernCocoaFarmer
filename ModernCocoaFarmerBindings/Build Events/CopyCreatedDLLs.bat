set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

cd %OutputDir%

(robocopy .\ ..\..\..\Celeste\CelesteEditor\bin\%Configuration%\ /IS /IT /xo) ^& exit 0