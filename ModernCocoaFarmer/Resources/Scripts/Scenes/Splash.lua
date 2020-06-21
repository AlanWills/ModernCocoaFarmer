---------------------------------------------------------------------------------
local Splash =
{
    SPLASH_SCENE_SCREEN_PATH = path.combine("Scenes", "Splash.scene"),
    SPLASH_ROOT_NAME = "SplashScene",
    SCREEN_TRANSITIONER_NAME = "SceneTransitioner",
}

---------------------------------------------------------------------------------
function Splash.new()
    Scene.load(Splash.SPLASH_SCENE_SCREEN_PATH)
    Splash._root = GameObject.find(Splash.SPLASH_ROOT_NAME)

    local screenTransitioner = Splash._root:findChild(Splash.SCREEN_TRANSITIONER_NAME)
    local eventTriggerer = screenTransitioner:findComponent("EventTriggerer")
    eventTriggerer:subscribeOnEventTriggeredCallback(Splash.hide)
end

---------------------------------------------------------------------------------
function Splash.hide()
    Splash._root:destroy()
    Splash._root = nil
    
    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

return Splash
