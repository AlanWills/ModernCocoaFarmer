local StartGameplayCommand = {}

---------------------------------------------------------------------------------
function StartGameplayCommand.execute()
    local gameplayScene = require "Scenes.Gameplay"
    local introVideo = require "Tutorials.IntroVideo"

    introVideo.showIntroVideoIfNecessary(gameplayScene.show)
end

return StartGameplayCommand