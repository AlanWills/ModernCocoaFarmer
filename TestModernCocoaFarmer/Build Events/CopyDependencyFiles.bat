set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

rem Debugging
rem echo %OutputDir% > log.txt
rem echo %OutputDir%..\..\..\..\3rdParty\DLL >> log.txt

cd %OutputDir%

(robocopy ..\..\..\..\Celeste\TestUtils\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\..\Celeste\CelesteTestUtils\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\..\ModernCocoaFarmerLibrary\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) & exit 0