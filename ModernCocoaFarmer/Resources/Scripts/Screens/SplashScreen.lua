local SplashScreen = {}

---------------------------------------------------------------------------------
SplashScreen.SPLASH_SCREEN_SCREEN_PATH = path.combine("Screens", "Splash.screen")
SplashScreen.SCREEN_TRANSITIONER_NAME = "ScreenTransitioner"

---------------------------------------------------------------------------------
local function transitionToMainMenu(caller)
    --caller:getScreen():die()

    local MainMenuScreen = require 'Screens.MainMenuScreen'
    MainMenuScreen.show()
end

---------------------------------------------------------------------------------
function SplashScreen.show()
    local splashScreen = Screen.load(SplashScreen.SPLASH_SCREEN_SCREEN_PATH)

    local screenTransitioner = splashScreen:findGameObject(SplashScreen.SCREEN_TRANSITIONER_NAME)
    local limitedLifeTime = screenTransitioner:findComponent("LimitedLifeTime")
    limitedLifeTime:subscribeOnDeathCallback(transitionToMainMenu)
end

return SplashScreen