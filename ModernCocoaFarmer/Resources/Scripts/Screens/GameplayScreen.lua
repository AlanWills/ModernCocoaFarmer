local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsBar = require 'UI.Notifications.NotificationsBar'

local GameplayScreen = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    NOTIFICATIONS_BAR_NAME = "NotificationsBar",
    LOCATIONS_UI_NAME = "LocationsUI",
}

---------------------------------------------------------------------------------
local function onTimeChanged(eventArgs, deltaTime, timeManager)
    timeManager:update(deltaTime)
end

---------------------------------------------------------------------------------
local function onGameEventTriggeredCallback(eventArgs, gameEvent)
    GameplayScreen.updateUI()
end

---------------------------------------------------------------------------------
function GameplayScreen.show()
    local timeManager = TimeManager.load(path.combine("Data", "Time", "TimeManager.asset"))
    local moneyManager = MoneyManager.load(path.combine("Data", "Money", "MoneyManager.asset"))
    local familyManager = FamilyManager.load(path.combine("Data", "Family", "FamilyManager.asset"))
    local locationsManager = LocationsManager.load(path.combine("Data", "Locations", "LocationsManager.asset"))
    local notificationManager = NotificationManager.load(path.combine("Data", "Notifications", "NotificationManager.asset"))

    local gameEventManager = GameEventManager.load(path.combine("Data", "Events", "GameEventManager.asset"))
    gameEventManager:setTimeManager(timeManager)
    gameEventManager:setMoneyManager(moneyManager)
    gameEventManager:setFamilyManager(familyManager)
    gameEventManager:setLocationsManager(locationsManager)
    gameEventManager:setNotificationManager(notificationManager)
    gameEventManager:subscribeOnGameEventTriggeredCallback(onGameEventTriggeredCallback)
       
    familyManager:addChild()
    familyManager:addChild()
    
    local gameplayScreen = Screen.load(GameplayScreen.GAMEPLAY_SCREEN_PATH)
    
    local timeComponent = gameplayScreen:findGameObject(GameplayScreen.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, timeManager)

    local locationsUI = gameplayScreen:findGameObject(GameplayScreen.LOCATIONS_UI_NAME)
    GameplayScreen._locationsUI = Class.new(LocationsUI, locationsManager, familyManager, locationsUI)

    local topBarGameObject = gameplayScreen:findGameObject(GameplayScreen.TOP_BAR_NAME)
    GameplayScreen._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        familyManager, 
        moneyManager,
        timeManager)
      
    local notificationsBar = gameplayScreen:findGameObject(GameplayScreen.NOTIFICATIONS_BAR_NAME)
    GameplayScreen._notificationsBar = Class.new(NotificationsBar, notificationsBar, notificationManager)

    GameplayScreen._timeManager = timeManager
    GameplayScreen._moneyManager = moneyManager
    GameplayScreen._familyManager = familyManager
    GameplayScreen._locationsManager = locationsManager
    GameplayScreen._notificationManager = notificationManager
    GameplayScreen._gameEventManager = gameEventManager
    
    GameplayScreen.updateUI()
end

---------------------------------------------------------------------------------
function GameplayScreen.updateUI()
    GameplayScreen._locationsUI:updateUI()
    GameplayScreen._topBar:updateUI()
end

return GameplayScreen