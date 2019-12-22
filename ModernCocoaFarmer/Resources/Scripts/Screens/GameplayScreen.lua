local Class = require 'OOP.Class'
local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local csd = require "UI.Family.ChildStatsDialog"
local TopBar = require "UI.TopBar"
local FamilyManager = require "Family.FamilyManager"

local GameplayScreen = Class.declare()

---------------------------------------------------------------------------------
GameplayScreen.GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen")
GameplayScreen.TOP_BAR_NAME = "TopBarBackground"

---------------------------------------------------------------------------------
function GameplayScreen.new()
    local gameplayScreen = Class.new(GameplayScreen)

    gameplayScreen:initializeModel()
    gameplayScreen:initializeScene()

    return gameplayScreen
end

---------------------------------------------------------------------------------
function GameplayScreen:initializeModel()
    self._familyManager = FamilyManager.new()
end

---------------------------------------------------------------------------------
function GameplayScreen:initializeScene()
    -- Either caches instances or resources in memory to allow quicker prefab instancing
    ibd.load()
    csd.load()
    
    local gameplayScreen = Screen.load(GameplayScreen.GAMEPLAY_SCREEN_PATH)
    ibm.initialize(gameplayScreen)

    local topBarGameObject = gameplayScreen:findGameObject(GameplayScreen.TOP_BAR_NAME)
    self._topBar = TopBar.new(topBarGameObject, self._familyManager)
end

return GameplayScreen