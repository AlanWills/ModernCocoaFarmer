set "ProjectDir=%1"
set "Configuration=%2"
set "Platform=%3"
set "OutputDir=bin\%Platform%\%Configuration%"
set "ResourcesDir=%OutputDir%\Resources"

cd %ProjectDir%

(robocopy ..\ModernCocoaFarmerLibrary\bin\%Platform%\%Configuration%\ %OutputDir% /E /IS /IT /XO)
(robocopy Resources %ResourcesDir% /E /IS /IT /XO)

echo "Executing Lua Script Validation"
call ..\CelesteEngine\DevTools\LuaScriptValidator\LuaScriptValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Lua Script Validation Failed"
  exit 1
)

echo "Lua Script Validation Passed"
echo "Executing Prefab Validation"
call ..\CelesteEngine\DevTools\PrefabValidator\PrefabValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Prefab Validation Failed"
  exit 1
)

echo "Prefab Validation Passed"
echo "Executing Scene Validation"
call ..\CelesteEngine\DevTools\SceneValidator\SceneValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Scene Validation Failed"
  exit 1
)

echo "Scene Validation Passed"

rem call ..\CelesteEngine\DevTools\ScriptableObjectValidator\ScriptableObjectValidator.exe %ResourcesDir%