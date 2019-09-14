local ibm = require "UI.InteractableBuildingsManager"
local ibd = require 'UI.InteractableBuildingDialog'

local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.screen")
local gameplayScreen = Screen.load(screenPath)

-- Set up Interactable Buildings manager to set up callbacks
--ibm.initialize(gameplayScreen)

-- Load interactable building dialog into resource manager so that it is cached
--ibd.load()