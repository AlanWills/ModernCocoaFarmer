local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsPanel = require 'UI.Notifications.NotificationsPanel'
local ModalDialogManager = require 'UI.Dialogs.ModalDialogManager'
local CommandManager = require 'Commands.CommandManager'
local AddChild = require 'Commands.Family.AddChild'
local ActivateLocation = require 'Commands.Locations.ActivateLocation'
local ElapseTime = require 'Commands.Time.ElapseTime'

---------------------------------------------------------------------------------
local Gameplay = 
{
    GAMEPLAY_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "Gameplay.scene"),
    GAMEPLAY_ROOT_NAME = "GameplayScene",
    TOP_BAR_NAME = "TopBar",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    NOTIFICATIONS_PANEL_NAME = "NotificationsPanel",
    LOCATIONS_UI_NAME = "LocationsUI",
    MODAL_DIALOG_MANAGER_NAME = "ModalDialogManager",
}

---------------------------------------------------------------------------------
local LocationNames = 
{
    FARM = "Cocoa Farm",
    HOME = "Home",
    HOSPITAL = "Hospital",
    MARKET = "Market",
    MOSQUE = "Mosque",
    SCHOOL = "School",
    WELL = "Well",
}

---------------------------------------------------------------------------------
local function onTimeChanged(deltaTime, commandManager)
    commandManager:execute(ElapseTime, deltaTime)
    commandManager:update()

    Gameplay.updateUI()
end

---------------------------------------------------------------------------------
function Gameplay.show()
    -- Scene Initialization
    Scene.load(Gameplay.GAMEPLAY_SCENE_PATH)
    
    -- Data Model Initialization
    local dataStore = DataStore.create()
    local timeManager = TimeManager.load(path.combine("Data", "Time", "TimeManager.asset"))
    local moneyManager = MoneyManager.load(path.combine("Data", "Money", "MoneyManager.asset"))
    local familyManager = FamilyManager.load(path.combine("Data", "Family", "FamilyManager.asset"))
    local locationsManager = LocationsManager.load(path.combine("Data", "Locations", "LocationsManager.asset"))
    local notificationManager = NotificationManager.load(path.combine("Data", "Notifications", "NotificationManager.asset"))
    local gameEventManager = GameEventManager.load(path.combine("Data", "Events", "GameEventManager.asset"))

    timeManager:setDataStore(dataStore)
    moneyManager:setDataStore(dataStore)
    familyManager:setDataStore(dataStore)
    locationsManager:setDataStore(dataStore)

    gameEventManager:setTimeManager(timeManager)
    gameEventManager:setMoneyManager(moneyManager)
    gameEventManager:setFamilyManager(familyManager)
    gameEventManager:setLocationsManager(locationsManager)
    gameEventManager:setNotificationManager(notificationManager)
    
    local modalDialogManagerGameObject = GameObject.find(Gameplay.MODAL_DIALOG_MANAGER_NAME)
    local modalDialogManager = Class.new(ModalDialogManager, modalDialogManagerGameObject)

    local commandManager = Class.new(CommandManager)
    commandManager.timeManager = timeManager
    commandManager.moneyManager = moneyManager
    commandManager.familyManager = familyManager
    commandManager.locationsManager = locationsManager
    commandManager.notificationManager = notificationManager
    commandManager.modalDialogManager = modalDialogManager
    
    Gameplay._dataStore = dataStore
    Gameplay._timeManager = timeManager
    Gameplay._moneyManager = moneyManager
    Gameplay._familyManager = familyManager
    Gameplay._locationsManager = locationsManager
    Gameplay._notificationManager = notificationManager
    Gameplay._gameEventManager = gameEventManager
    Gameplay._modalDialogManager = modalDialogManager
    Gameplay._commandManager = commandManager

    -- Family Initialization
    commandManager:execute(AddChild)
    commandManager:execute(AddChild)

    -- Location Initialization
    for k, v in pairs(LocationNames) do
        commandManager:execute(ActivateLocation, v)
    end

    -- Extra UI initialization
    local timeComponent = GameObject.find(Gameplay.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, commandManager)

    local locationsUI = GameObject.find(Gameplay.LOCATIONS_UI_NAME)
    Gameplay._locationsUI = Class.new(LocationsUI, commandManager, dataStore, locationsUI)

    local topBarGameObject = GameObject.find(Gameplay.TOP_BAR_NAME)
    Gameplay._topBar = Class.new(
        TopBar,
        commandManager,
        dataStore,
        topBarGameObject)
      
    local notificationsPanel = GameObject.find(Gameplay.NOTIFICATIONS_PANEL_NAME)
    Gameplay._notificationsBar = Class.new(NotificationsPanel, commandManager, notificationsPanel)

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

    Gameplay._modalDialogManager:destroyDialogs()
end

return Gameplay
