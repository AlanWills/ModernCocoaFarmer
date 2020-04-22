local Splash = require 'Scenes.Splash'
local StartGameplayCommand = require 'Commands.StartGameplayCommand'

Mouse.setCursor(path.combine("Textures", "UI", "Utility", "Cursor.png"))

local quickStart = true

if not quickStart then
    Splash.show()
else
    StartGameplayCommand.execute()
end