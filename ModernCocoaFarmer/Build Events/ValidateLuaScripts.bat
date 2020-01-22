set "ProjectDir=%1"
set "ResourcesDir=%2"

cd %ProjectDir%

call ..\CelesteEngine\DevTools\LuaScriptValidator\LuaScriptValidator.exe %ResourcesDir%