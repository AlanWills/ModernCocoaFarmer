local quickStart = false

Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "DebugTools.screen"))

if not quickStart then
    Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Splash.screen"))
else
    require 'Gameplay.StartGameplay'
end