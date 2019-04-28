addToLuaPath(Resources.getResourcesDirectory() .. "\\..\\..\\CelesteEngine\\Resources\\Scripts\\?.lua;")

require "Engine"

--[[local settingsPath = path.combine(Resources.getResourcesDirectory(), "Data", "Settings", "GameSettings.asset")
local settings = GameSettings.load(settingsPath)

setMasterVolume(settings:getMasterVolume())
setMusicVolume(settings:getMusicVolume())
setSFXVolume(settings:getSFXVolume())

Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "DebugTools.asset"))
Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "PersistentStartupAndMainMenu.asset"))
Screen.load(path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "SplashScreen.asset"))--]]