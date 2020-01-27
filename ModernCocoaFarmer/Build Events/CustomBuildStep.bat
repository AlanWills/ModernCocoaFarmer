set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"
set "ResourcesDir=%4"
set "ProjectDir=%5"

rem call "Build Events\CopyDependencyFiles.bat" %OutputDir% %Configuration% %Platform% %ResourcesDir%
call "Build Events\ValidateLuaScripts.bat" %ProjectDir% %ResourcesDir%

rem call "$(ProjectDir)Build Events\ValidatePrefabs.bat" "$(ProjectDir)" "$(TargetDir)Resources"
rem call "$(ProjectDir)Build Events\ValidateScenes.bat" "$(ProjectDir)" "$(TargetDir)Resources"