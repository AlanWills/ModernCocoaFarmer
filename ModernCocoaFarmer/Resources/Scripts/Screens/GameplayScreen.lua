local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local csd = require "UI.Family.ChildStatsDialog"
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

    -- Load UI
    ibd.load()
    csd.load()

    -- Temporarily show the dialog for UI testing
    local dummyChildInfo = ChildInformation.create("Test")
    csd.show(gameplayScreen, dummyChildInfo)
end

return gps