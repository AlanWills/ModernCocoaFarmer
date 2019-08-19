local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.screen")
local gameplayScreen = Screen.load(screenPath)

GameplayManager.instance():startGameplay(gameplayScreen)