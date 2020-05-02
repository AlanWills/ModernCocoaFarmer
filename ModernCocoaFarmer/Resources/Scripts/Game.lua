local Splash = require 'Scenes.Splash'
local StartGameplayCommand = require 'Commands.StartGameplayCommand'
local Class = require 'OOP.Class'
local Load = require 'Commands.State.Load'
local GameplayStateConstants = require 'State.GameplayStateConstants'

Mouse.setCursor(path.combine("Textures", "UI", "Utility", "Cursor.png"))

local quickStart = true
local loadGame = false

if not quickStart then
    Splash.show()
elseif loadGame then
    Class.new(Load, GameplayStateConstants.SAVE_DIRECTORY):execute()
else
    StartGameplayCommand.execute()
end