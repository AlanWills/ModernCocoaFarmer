local ibd = require 'UI.InteractableBuildingDialog'

local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.screen")
local gameplayScreen = Screen.load(screenPath)

-- Load interactable building dialog into resource manager so that it is cached
ibd.load()
ibd.show(gameplayScreen)

-- Start by moving interactable building dialog code to lua and figuring out how to give the show function the correct prefab
-- Need casting for scriptable objects to be able to load building information in using ScriptableObject.load
-- Can do this similar way to handle?
-- Will also need to add BuildingInformation script commands and for now can just add factory funcs there ala GameSettingsScriptCommands

--GameplayManager.instance():startGameplay(gameplayScreen)