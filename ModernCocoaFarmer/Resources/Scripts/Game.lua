local quickStart = true

Screen.load(path.combine(Resources.getResourcesDirectory(), "Screens", "DebugTools.screen"))

if not quickStart then
    Screen.load(path.combine(Resources.getResourcesDirectory(), "Screens", "Splash.screen"))
else
    require 'Gameplay.StartGameplay'
end