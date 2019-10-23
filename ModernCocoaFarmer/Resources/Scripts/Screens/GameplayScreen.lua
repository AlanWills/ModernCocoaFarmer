local ibm = require "UI.InteractableBuildingsManager"
local ibd = require 'UI.InteractableBuildingDialog'

local gps = {}

---------------------------------------------------------------------------------
gps.GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.screen")

---------------------------------------------------------------------------------
function gps.show()
    local gameplayScreen = Screen.load(gps.GAMEPLAY_SCREEN_PATH)

    -- Set up Interactable Buildings manager to set up callbacks
    ibm.initialize(gameplayScreen)

    -- Load interactable building dialog into resource manager so that it is cached and quicker to create at runtime
    ibd.load()
end

return gps