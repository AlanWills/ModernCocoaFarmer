local MCFComponents = require 'Components.MCFComponents'
local SplashScene = require 'Scenes.Splash'
local StartGameplayCommand = require 'Commands.StartGameplayCommand'

local quickStart = false

Scene.load(path.combine(Resources.getResourcesDirectory(), "Scenes", "DebugTools.scene"))

if not quickStart then
    SplashScene.show()
else
    StartGameplayCommand.execute()
end