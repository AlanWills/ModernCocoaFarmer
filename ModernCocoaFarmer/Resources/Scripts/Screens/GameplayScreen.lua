local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local fam = require "Family.FamilyManager"

local gps = {}

---------------------------------------------------------------------------------
gps.GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen")

---------------------------------------------------------------------------------
function gps.show()
    local gameplayScreen = Screen.load(gps.GAMEPLAY_SCREEN_PATH)

    -- Set up Interactable Buildings manager to set up callbacks
    ibm.initialize(gameplayScreen)

    -- Set up Family
    fam.initialize(gameplayScreen)

    -- Load interactable building dialog into resource manager so that it is cached and quicker to create at runtime
    ibd.load()
end

return gps