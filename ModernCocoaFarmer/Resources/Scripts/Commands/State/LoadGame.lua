local Class = require 'OOP.Class'
local GameplayState = require 'State.GameplayState'

---------------------------------------------------------------------------------
local LoadGame = {}

---------------------------------------------------------------------------------
function LoadGame:new(saveDirectory)
    self._saveDirectory = saveDirectory or GameplayState.SAVE_DIRECTORY
end

---------------------------------------------------------------------------------
function LoadGame:execute()
    log("Loading game")
    
    local Gameplay = require "Scenes.Gameplay"
    local Loading = require 'Scenes.Loading'
    local ShowIntroVideo = require 'Commands.Tutorials.ShowIntroVideo'

    Loading.show(
        function()
            Gameplay.new(self._saveDirectory)
        end, 
        function()
            Class.new(ShowIntroVideo, Gameplay.show):execute() 
        end)
end

return LoadGame