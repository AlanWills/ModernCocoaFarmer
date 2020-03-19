local MCFComponents = require 'Components.MCFComponents'
local Splash = require 'Scenes.Splash'
local StartGameplayCommand = require 'Commands.StartGameplayCommand'

local quickStart = false

Scene.load(path.combine(Resources.getResourcesDirectory(), "Scenes", "DebugTools.scene"))

if not quickStart then
    Splash.show()
else
    StartGameplayCommand.execute()
end