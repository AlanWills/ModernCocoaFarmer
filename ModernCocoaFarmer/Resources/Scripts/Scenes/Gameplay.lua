local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsBar = require 'UI.Notifications.NotificationsBar'

local GameplayScene = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "Gameplay.scene"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    NOTIFICATIONS_BAR_NAME = "NotificationsBar",
    LOCATIONS_UI_NAME = "LocationsUI",
}

---------------------------------------------------------------------------------
local function onTimeChanged(deltaTime, timeManager)
    timeManager:update(deltaTime)
end

---------------------------------------------------------------------------------
local function onGameEventTriggeredCallback(gameEvent)
    GameplayScene.updateUI()
end

---------------------------------------------------------------------------------
function GameplayScene.show()
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
    
    Scene.load(GameplayScene.GAMEPLAY_SCREEN_PATH)
    
    local timeComponent = GameObject.find(GameplayScene.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, timeManager)

    local locationsUI = GameObject.find(GameplayScene.LOCATIONS_UI_NAME)
    GameplayScene._locationsUI = Class.new(LocationsUI, locationsManager, familyManager, locationsUI)

    local topBarGameObject = GameObject.find(GameplayScene.TOP_BAR_NAME)
    GameplayScene._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        familyManager, 
        moneyManager,
        timeManager)
      
    local notificationsBar = GameObject.find(GameplayScene.NOTIFICATIONS_BAR_NAME)
    GameplayScene._notificationsBar = Class.new(NotificationsBar, notificationsBar, notificationManager)

    GameplayScene._timeManager = timeManager
    GameplayScene._moneyManager = moneyManager
    GameplayScene._familyManager = familyManager
    GameplayScene._locationsManager = locationsManager
    GameplayScene._notificationManager = notificationManager
    GameplayScene._gameEventManager = gameEventManager
    
    GameplayScene.updateUI()
end

---------------------------------------------------------------------------------
function GameplayScene.updateUI()
    GameplayScene._locationsUI:updateUI()
    GameplayScene._topBar:updateUI()
end

return GameplayScene
