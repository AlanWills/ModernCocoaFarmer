local SplashScreen = require 'Screens.SplashScreen'
local StartGameplayCommand = require 'Commands.StartGameplayCommand'

local quickStart = true

Screen.load(path.combine(Resources.getResourcesDirectory(), "Screens", "DebugTools.screen"))

if not quickStart then
    SplashScreen.show()
else
    StartGameplayCommand.execute()
end