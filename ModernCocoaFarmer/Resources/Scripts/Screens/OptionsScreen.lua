local OptionsScreen = {}

---------------------------------------------------------------------------------
OptionsScreen.OPTIONS_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Options.screen")

---------------------------------------------------------------------------------
function OptionsScreen.show()
    local optionsScreen = Screen.load(OptionsScreen.OPTIONS_SCREEN_PATH)
end

return OptionsScreen