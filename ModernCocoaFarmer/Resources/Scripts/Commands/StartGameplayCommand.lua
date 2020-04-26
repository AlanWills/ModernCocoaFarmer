local GameplayState = require 'State.GameplayState'
local Class = require 'OOP.Class'

local StartGameplayCommand = {}

---------------------------------------------------------------------------------
function StartGameplayCommand.startGameplay()
    local state = Class.new(GameplayState)
    state:load()

    local gameplayScene = require "Scenes.Gameplay"
    gameplayScene.show(state)
end

---------------------------------------------------------------------------------
function StartGameplayCommand.execute()
    local introVideo = require "Tutorials.IntroVideo"
    introVideo.showIntroVideoIfNecessary(StartGameplayCommand.startGameplay)
end

return StartGameplayCommand