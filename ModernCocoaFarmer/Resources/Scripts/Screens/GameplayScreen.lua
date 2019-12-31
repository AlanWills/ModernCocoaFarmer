local Class = require 'OOP.Class'
local ibm = require "UI.InteractableBuildingsManager"
local ibd = require "UI.InteractableBuildingDialog"
local csd = require "UI.Family.ChildStatsDialog"
local TopBar = require "UI.TopBar"
local EventNotification = require 'UI.Events.EventNotification'
local GameEventManager = require 'Events.GameEventManager'
local WelcomeToZegoua = require 'Events.WelcomeToZegoua'

local GameplayScreen = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    EVENT_NOTIFICATIONS_NAME = "EventNotifications"
}

---------------------------------------------------------------------------------
local function onTimeChanged(eventArgs, deltaTime, timeManager)
    timeManager:update(deltaTime)
end

---------------------------------------------------------------------------------
function GameplayScreen.show()
    -- Either caches instances or resources in memory to allow quicker prefab instancing
    ibd.load()
    csd.load()
    
    local gameplayScreen = Screen.load(GameplayScreen.GAMEPLAY_SCREEN_PATH)
    ibm.initialize(gameplayScreen)

    GameplayScreen._timeManager = TimeManager.create("TimeManager")
    GameplayScreen._moneyManager = MoneyManager.create("MoneyManager")
    GameplayScreen._familyManager = FamilyManager.create("FamilyManager")
    GameplayScreen._eventManager = Class.new(
        GameEventManager, 
        gameplayScreen:findGameObject(GameplayScreen.EVENT_NOTIFICATIONS_NAME), 
        GameplayScreen._familyManager,
        GameplayScreen._moneyManager,
        GameplayScreen._timeManager)
        
    local topBarGameObject = gameplayScreen:findGameObject(GameplayScreen.TOP_BAR_NAME)
    GameplayScreen._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        GameplayScreen._familyManager, 
        GameplayScreen._moneyManager,
        GameplayScreen._timeManager)
        
    local timeComponent = gameplayScreen:findGameObject(GameplayScreen.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, GameplayScreen._timeManager)

    GameplayScreen._eventManager:triggerEvent(WelcomeToZegoua)
end

return GameplayScreen