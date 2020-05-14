local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsPanel = require 'UI.Notifications.NotificationsPanel'
local ModalDialogManager = require 'UI.Dialogs.ModalDialogManager'
local CommandManager = require 'Commands.CommandManager'
local ActivateLocation = require 'Commands.Locations.ActivateLocation'
local ElapseTime = require 'Commands.Time.ElapseTime'
local GameEventManager = require 'GameEvents.GameEventManager'

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
    FARM = "Farm",
    HOME = "Home",
    HOSPITAL = "Hospital",
    MARKET = "Market",
    MOSQUE = "Mosque",
    SCHOOL = "School",
    WELL = "Well",
}

---------------------------------------------------------------------------------
local function onTimeChanged(deltaTime, commandManager)
    Gameplay.updateUI()

    commandManager:execute(ElapseTime, deltaTime)
end

---------------------------------------------------------------------------------
function Gameplay.show(state)
    -- Scene Initialization
    Scene.load(Gameplay.GAMEPLAY_SCENE_PATH)
    
    local modalDialogManagerGameObject = GameObject.find(Gameplay.MODAL_DIALOG_MANAGER_NAME)
    state.modalDialogManager = Class.new(ModalDialogManager, modalDialogManagerGameObject)

    local commandManager = Class.new(CommandManager, state)
    local gameEventManager = Class.new(GameEventManager, commandManager)
    local dataSystem = System.getDataSystem()

    Gameplay._state = state
    Gameplay._commandManager = commandManager
    Gameplay._gameEventManager = gameEventManager

    -- Extra UI initialization
    local timeComponent = GameObject.find(Gameplay.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, commandManager)

    local locationsUI = GameObject.find(Gameplay.LOCATIONS_UI_NAME)
    Gameplay._locationsUI = Class.new(LocationsUI, commandManager, dataSystem, locationsUI)

    local topBarGameObject = GameObject.find(Gameplay.TOP_BAR_NAME)
    Gameplay._topBar = Class.new(
        TopBar,
        commandManager,
        dataSystem,
        topBarGameObject)
      
    local notificationsPanel = GameObject.find(Gameplay.NOTIFICATIONS_PANEL_NAME)
    Gameplay._notificationsBar = Class.new(NotificationsPanel, commandManager, notificationsPanel)
    
    -- Location Initialization
    for k, v in pairs(LocationNames) do
        commandManager:execute(ActivateLocation, v)
    end

    Gameplay.updateUI()
    Gameplay.addDolceWindows();
end

---------------------------------------------------------------------------------
function Gameplay.hide()
    Gameplay._state = nil
    Gameplay._commandManager = nil
    Gameplay._gameEventManager = nil
    Gameplay._locationsUI = nil
    Gameplay._topBar = nil
    Gameplay._notificationsBar = nil
    Gameplay.removeDolceWindows();

    GameObject.find(Gameplay.GAMEPLAY_ROOT_NAME):destroy()
end

---------------------------------------------------------------------------------
function Gameplay.updateUI()
    Gameplay._locationsUI:updateUI()
    Gameplay._topBar:updateUI()

    Gameplay._state.modalDialogManager:destroyDialogs()
end

---------------------------------------------------------------------------------
function Gameplay.addDolceWindows()
    local MoneyManagerDolceWindow = require 'Debug.DolceWindows.MoneyManagerDolceWindow'
    local TimeManagerDolceWindow = require 'Debug.DolceWindows.TimeManagerDolceWindow'
    local FamilyManagerDolceWindow = require 'Debug.DolceWindows.FamilyManagerDolceWindow'

    Dolce.instance:addWindow(MoneyManagerDolceWindow.NAME, Class.new(MoneyManagerDolceWindow, Gameplay._state.moneyManager))
    Dolce.instance:addWindow(TimeManagerDolceWindow.NAME, Class.new(TimeManagerDolceWindow, Gameplay._state.timeManager))
    Dolce.instance:addWindow(FamilyManagerDolceWindow.NAME, Class.new(FamilyManagerDolceWindow, Gameplay._state.familyManager))
end

---------------------------------------------------------------------------------
function Gameplay.removeDolceWindows()
    Dolce.instance:removeWindow(MoneyManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(TimeManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(FamilyManagerDolceWindow.NAME)
end

return Gameplay
