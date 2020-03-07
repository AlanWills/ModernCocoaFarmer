---------------------------------------------------------------------------------
local Splash =
{
    SPLASH_SCENE_SCREEN_PATH = path.combine("Scenes", "Splash.scene"),
    SPLASH_ROOT_NAME = "SplashScene",
    SCREEN_TRANSITIONER_NAME = "SceneTransitioner",
}

---------------------------------------------------------------------------------
function transitionToMainMenu(caller)
    local Splash = require 'Scenes.Splash'
    Splash.hide()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
function Splash.show()
    Scene.load(Splash.SPLASH_SCENE_SCREEN_PATH)

    local screenTransitioner = GameObject.find(Splash.SCREEN_TRANSITIONER_NAME)
    local eventTriggerer = screenTransitioner:findComponent("EventTriggerer")
    eventTriggerer:subscribeOnEventTriggered(transitionToMainMenu)
end

---------------------------------------------------------------------------------
function Splash.hide()
    GameObject.find(Splash.SPLASH_ROOT_NAME):destroy()
end

return Splash
