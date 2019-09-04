local ibd = require 'UI.InteractableBuildingDialog'

local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.screen")
local gameplayScreen = Screen.load(screenPath)

-- Load interactable building dialog into resource manager so that it is cached
ibd.load()
ibd.show(gameplayScreen)
--local dialog = InteractableBuildingDialog.new()
--dialog:show(gameplayScreen)

-- Then when we want to show the interactable building dialog, we create a new instance and instantiate the prefab
-- Currently, we don't need gameplay manager or interactable buildings manager or interactable building dialog except for events
-- If we can hook those events up in lua we're gucci
-- Start by moving interactable building dialog code to lua and figuring out how to give the show function the correct prefab
-- Need casting for scriptable objects to be able to load building information in using ScriptableObject.load
-- Can do this similar way to handle?
-- Will also need to add BuildingInformation script commands and for now can just add factory funcs there ala GameSettingsScriptCommands

--GameplayManager.instance():startGameplay(gameplayScreen)