local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local csd = require "UI.Family.ChildStatsDialog"
local topBar = require "UI.TopBar"
local familyManager = require "Family.FamilyManager"

local gps = {}

---------------------------------------------------------------------------------
gps.GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen")
gps.TOP_BAR_NAME = "TopBarBackground"

---------------------------------------------------------------------------------
local function initializeModel()
    familyManager.initialize()
end

---------------------------------------------------------------------------------
local function initializeUI(gameplayScreen)
    -- Either caches instances or resources in memory to allow quicker prefab instancing
    ibd.load()
    csd.load()
    
    local gameplayScreen = Screen.load(gps.GAMEPLAY_SCREEN_PATH)
    ibm.initialize(gameplayScreen)

    local topBarGameObject = gameplayScreen:findGameObject(gps.TOP_BAR_NAME)
    topBar.initialize(topBarGameObject, familyManager)
end

---------------------------------------------------------------------------------
function gps.show()
    initializeModel()
    initializeUI()
end

return gps