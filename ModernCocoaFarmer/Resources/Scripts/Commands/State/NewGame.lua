local Class = require 'OOP.Class'
local GameplayState = require 'State.GameplayState'

---------------------------------------------------------------------------------
local NewGame = {}

---------------------------------------------------------------------------------
function NewGame:execute()
    log("Launching new game")
    
    local Gameplay = require "Scenes.Gameplay"
    local Loading = require 'Scenes.Loading'
    local ShowIntroVideo = require 'Commands.Tutorials.ShowIntroVideo'

    Loading.show(
        function()
            Gameplay.new()
        end, 
        function() 
            Class.new(ShowIntroVideo, Gameplay.show):execute() 
        end)
end

return NewGame