local StartGameplayCommand = {}

---------------------------------------------------------------------------------
function StartGameplayCommand.execute()
    local gameplayScreen = require "Screens.GameplayScreen"
    local introVideo = require "Tutorials.IntroVideo"

    introVideo.showIntroVideoIfNecessary(gameplayScreen.show)
end

return StartGameplayCommand