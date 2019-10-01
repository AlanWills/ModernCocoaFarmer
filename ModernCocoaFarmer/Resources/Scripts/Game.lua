local quickStart = true

Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "DebugTools.screen"))

if not quickStart then
    Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Splash.screen"))
else
    --Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Loading.screen"))
    require 'Gameplay.StartGameplay'
end