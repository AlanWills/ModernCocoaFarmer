local SplashScene = {}

---------------------------------------------------------------------------------
SplashScene.SPLASH_SCREEN_SCREEN_PATH = path.combine("Scenes", "Splash.scene")
SplashScene.SPLASH_SCREEN_ROOT_NAME = "SplashScene"
SplashScene.SCREEN_TRANSITIONER_NAME = "SceneTransitioner"

---------------------------------------------------------------------------------
local function transitionToMainMenu(caller)
    GameObject.find(SplashScene.SPLASH_SCREEN_ROOT_NAME):destroy()

    local MainMenuScene = require 'Scenes.MainMenu'
    MainMenuScene.show()
end

---------------------------------------------------------------------------------
function SplashScene.show()
    Scene.load(SplashScene.SPLASH_SCREEN_SCREEN_PATH)

    local screenTransitioner = GameObject.find(SplashScene.SCREEN_TRANSITIONER_NAME)
    local eventTriggerer = screenTransitioner:findComponent("EventTriggerer")
    eventTriggerer:subscribeOnEventTriggered(transitionToMainMenu)
end

return SplashScene
