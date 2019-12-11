local MainMenuScreen = {}

---------------------------------------------------------------------------------
MainMenuScreen.MAIN_MENU_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen")

---------------------------------------------------------------------------------
function gps.show()
    local mainMenuScreen = Screen.load(MainMenuScreen.MAIN_MENU_SCREEN_PATH)
end

return MainMenuScreen