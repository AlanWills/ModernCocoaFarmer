local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsBar = require 'UI.Notifications.NotificationsBar'
local ModalDialogManager = require 'UI.Dialogs.ModalDialogManager'
local CommandManager = require 'Commands.CommandManager'
local AddChild = require 'Commands.Family.AddChild'
local ElapseTime = require 'Commands.Time.ElapseTime'

local Gameplay = 
{
    GAMEPLAY_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "Gameplay.scene"),
    GAMEPLAY_ROOT_NAME = "GameplayScene",
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    NOTIFICATIONS_BAR_NAME = "NotificationsBar",
    LOCATIONS_UI_NAME = "LocationsUI",
    MODAL_DIALOG_MANAGER_NAME = "ModalDialogManager",
}

---------------------------------------------------------------------------------
local function onTimeChanged(deltaTime, commandManager)
    commandManager:execute(ElapseTime, deltaTime)
    commandManager:update()
end

---------------------------------------------------------------------------------
local function onGameEventTriggeredCallback(gameEvent)
    Gameplay.updateUI()
end

---------------------------------------------------------------------------------
function Gameplay.show()
    -- Data Model Initialization
    local dataStore = DataStore.create()
    local timeManager = TimeManager.load(path.combine("Data", "Time", "TimeManager.asset"))
    local moneyManager = MoneyManager.load(path.combine("Data", "Money", "MoneyManager.asset"))
    local familyManager = FamilyManager.load(path.combine("Data", "Family", "FamilyManager.asset"))
    local locationsManager = LocationsManager.load(path.combine("Data", "Locations", "LocationsManager.asset"))
    local notificationManager = NotificationManager.load(path.combine("Data", "Notifications", "NotificationManager.asset"))
    local gameEventManager = GameEventManager.load(path.combine("Data", "Events", "GameEventManager.asset"))

    moneyManager:setDataStore(dataStore)
    
    gameEventManager:setTimeManager(timeManager)
    gameEventManager:setMoneyManager(moneyManager)
    gameEventManager:setFamilyManager(familyManager)
    gameEventManager:setLocationsManager(locationsManager)
    gameEventManager:setNotificationManager(notificationManager)
    gameEventManager:subscribeOnGameEventTriggeredCallback(onGameEventTriggeredCallback)
    
    local modalDialogManagerGameObject = GameObject.find(Gameplay.MODAL_DIALOG_MANAGER_NAME)
    local modalDialogManager = Class.new(ModalDialogManager, modalDialogManagerGameObject)

    local state =
    {
        timeManager = timeManager,
        moneyManager = moneyManager,
        familyManager = familyManager,
        locationsManager = locationsManager,
        notificationManager = notificationManager,
        modalDialogManager = modalDialogManager,
    }
    Gameplay._commandManager = Class.new(CommandManager, state)

    -- Initial family set up
    Gameplay._commandManager:execute(AddChild)
    Gameplay._commandManager:execute(AddChild)

    -- Scene Initialization
    Scene.load(Gameplay.GAMEPLAY_SCENE_PATH)
    
    local timeComponent = GameObject.find(Gameplay.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, Gameplay._commandManager)

    local locationsUI = GameObject.find(Gameplay.LOCATIONS_UI_NAME)
    Gameplay._locationsUI = Class.new(LocationsUI, locationsManager, familyManager, locationsUI)

    local topBarGameObject = GameObject.find(Gameplay.TOP_BAR_NAME)
    Gameplay._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        familyManager, 
        dataStore,
        timeManager)
      
    local notificationsBar = GameObject.find(Gameplay.NOTIFICATIONS_BAR_NAME)
    Gameplay._notificationsBar = Class.new(NotificationsBar, notificationsBar, notificationManager)

    Gameplay.updateUI()
end

---------------------------------------------------------------------------------
function Gameplay.hide()
    GameObject.find(Gameplay.GAMEPLAY_ROOT_NAME):destroy()
end

---------------------------------------------------------------------------------
function Gameplay.updateUI()
    Gameplay._locationsUI:updateUI()
    Gameplay._topBar:updateUI()
end

return Gameplay
