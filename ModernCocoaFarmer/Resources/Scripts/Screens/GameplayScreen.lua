local Class = require 'OOP.Class'
local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local csd = require "UI.Family.ChildStatsDialog"
local TopBar = require "UI.TopBar"
local EventNotification = require 'UI.Events.EventNotification'
local FamilyManager = require "Family.FamilyManager"
local MoneyManager = require 'Money.MoneyManager'
local TimeManager = require 'Time.TimeManager'
local GameEventManager = require 'Events.GameEventManager'

local GameplayScreen = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    EVENT_NOTIFICATIONS_NAME = "EventNotifications"
}

---------------------------------------------------------------------------------
function GameplayScreen.show()
    -- Either caches instances or resources in memory to allow quicker prefab instancing
    ibd.load()
    csd.load()
    
    local gameplayScreen = Screen.load(GameplayScreen.GAMEPLAY_SCREEN_PATH)
    ibm.initialize(gameplayScreen)

    local timeComponent = gameplayScreen:findGameObject(GameplayScreen.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    GameplayScreen._timeManager = Class.new(TimeManager, timeComponent)
    GameplayScreen._moneyManager = Class.new(MoneyManager)
    GameplayScreen._familyManager = Class.new(FamilyManager)
    GameplayScreen._eventManager = Class.new(
        GameEventManager, 
        gameplayScreen:findGameObject(GameplayScreen.EVENT_NOTIFICATIONS_NAME, 
        GameplayScreen._timeManager)

    local topBarGameObject = gameplayScreen:findGameObject(GameplayScreen.TOP_BAR_NAME)
    GameplayScreen._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        GameplayScreen._familyManager, 
        GameplayScreen._moneyManager,
        GameplayScreen._timeManager)
end

return GameplayScreen