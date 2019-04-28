package.path = Resources.getResourcesDirectory() .. "\\..\\..\\CelesteEngine\\CelesteEngine\\Resources\\Scripts\\?.lua;" .. package.path

require "Engine"

-- Delete these when we make the application automatic
WindowSettings.apply(path.combine(Resources.getResourcesDirectory(), "Data", "Settings", "WindowSettings.asset"))
GameSettings.apply(path.combine(Resources.getResourcesDirectory(), "Data", "Settings", "GameSettings.asset"))

--[[local settingsPath = path.combine(Resources.getResourcesDirectory(), "Data", "Settings", "GameSettings.asset")
local settings = GameSettings.load(settingsPath)

setMasterVolume(settings:getMasterVolume())
setMusicVolume(settings:getMusicVolume())
setSFXVolume(settings:getSFXVolume())

Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "DebugTools.asset"))
Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "PersistentStartupAndMainMenu.asset"))
Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "SplashScreen.asset"))--]]