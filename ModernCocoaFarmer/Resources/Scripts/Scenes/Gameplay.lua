local Class = require 'OOP.Class'
local GameplayState = require 'State.GameplayState'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local NotificationsPanel = require 'UI.Notifications.NotificationsPanel'
local ModalDialogManager = require 'UI.Dialogs.ModalDialogManager'
local CommandManager = require 'Commands.CommandManager'
local ActivateLocation = require 'Commands.Locations.ActivateLocation'
local ElapseTime = require 'Commands.Time.ElapseTime'
local Play = require 'Commands.Time.Play'
local GameEventManager = require 'GameEvents.GameEventManager'

-- Dolce Windows
local GameEventManagerDolceWindow = require 'Debug.DolceWindows.GameEventManagerDolceWindow'
local CommandManagerDolceWindow = require 'Debug.DolceWindows.CommandManagerDolceWindow'
local MoneyManagerDolceWindow = require 'Debug.DolceWindows.MoneyManagerDolceWindow'
local TimeManagerDolceWindow = require 'Debug.DolceWindows.TimeManagerDolceWindow'
local FamilyManagerDolceWindow = require 'Debug.DolceWindows.FamilyManagerDolceWindow'

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
function Gameplay.new(saveDirectory)
    log("Loading state")
    Gameplay._state = Class.new(GameplayState, saveDirectory)
    Gameplay._state:load()

    coroutine.yield()

    -- Sound loading
    for i, soundPath in ipairs(Gameplay.REQUIRED_SOUNDS) do
        log("Loading " .. soundPath)
        Resources.loadSound(soundPath)
        coroutine.yield()
    end

    coroutine.yield()
    
    -- Texture loading
    for i, texturePath in ipairs(Gameplay.REQUIRED_TEXTURES) do
        log("Loading " .. texturePath)
        Resources.loadTexture2D(texturePath)
        coroutine.yield()
    end

    -- Prefab loading
    for i, prefabPath in ipairs(Gameplay.REQUIRED_PREFABS) do
        log("Loading " .. prefabPath)
        Resources.loadPrefab(prefabPath)
        coroutine.yield()
    end

    coroutine.yield()

    log("Loading gameplay scene")

    Scene.load(Gameplay.GAMEPLAY_SCENE_PATH)
    Gameplay._root = GameObject.find(Gameplay.GAMEPLAY_ROOT_NAME)

    coroutine.yield()

    log("Initializing managers")

    local modalDialogManagerGameObject = GameObject.find(Gameplay.MODAL_DIALOG_MANAGER_NAME)
    Gameplay._state.modalDialogManager = Class.new(ModalDialogManager, modalDialogManagerGameObject)

    local commandManager = Class.new(CommandManager, Gameplay._state)
    local gameEventManager = Class.new(GameEventManager, commandManager)

    Gameplay._commandManager = commandManager
    Gameplay._gameEventManager = gameEventManager

    coroutine.yield()

    log("Initializing UI")

    local locationsUI = GameObject.find(Gameplay.LOCATIONS_UI_NAME)
    Gameplay._locationsUI = Class.new(LocationsUI, commandManager, locationsUI)

    local topBarGameObject = GameObject.find(Gameplay.TOP_BAR_NAME)
    Gameplay._topBar = Class.new(
        TopBar,
        commandManager,
        topBarGameObject)
      
    local notificationsPanel = GameObject.find(Gameplay.NOTIFICATIONS_PANEL_NAME)
    Gameplay._notificationsBar = Class.new(NotificationsPanel, commandManager, notificationsPanel)
    
    coroutine.yield()

    log("Initializing locations")

    -- Location Initialization
    for k, v in pairs(LocationNames) do
        commandManager:execute(ActivateLocation, v)
    end

    coroutine.yield()

    log("Adding Dolce windows")
    Gameplay.addDolceWindows()
end

---------------------------------------------------------------------------------
function Gameplay.update(deltaTime)
    Gameplay._state.modalDialogManager:destroyDialogs()
    Gameplay._commandManager:execute(ElapseTime, deltaTime)
end

---------------------------------------------------------------------------------
function Gameplay.show()
    log("Showing Gameplay scene")
    Gameplay._timeNotifierHandle = System.getTimeNotifierSystem():subscribe(Gameplay.update)
    Gameplay._root:setActive(true)
    Gameplay._root:findComponent("AudioSource"):play()
    Gameplay._commandManager:execute(Play)
end

---------------------------------------------------------------------------------
function Gameplay.hide()
    log("Hiding Gameplay scene")
    System.getTimeNotifierSystem():unsubscribe(Gameplay._timeNotifierHandle)

    Gameplay._timeNotifierHandle = 0
    Gameplay._state = nil
    Gameplay._commandManager = nil
    Gameplay._gameEventManager = nil
    Gameplay._locationsUI = nil
    Gameplay._topBar = nil
    Gameplay._notificationsBar = nil
    Gameplay._root:destroy()
    Gameplay.removeDolceWindows()
end

---------------------------------------------------------------------------------
function Gameplay.addDolceWindows()
    Dolce.instance:addWindow(GameEventManagerDolceWindow.NAME, Class.new(GameEventManagerDolceWindow, Gameplay._gameEventManager))
    Dolce.instance:addWindow(CommandManagerDolceWindow.NAME, Class.new(CommandManagerDolceWindow, Gameplay._commandManager))
    Dolce.instance:addWindow(MoneyManagerDolceWindow.NAME, Class.new(MoneyManagerDolceWindow, Gameplay._state.moneyManager))
    Dolce.instance:addWindow(TimeManagerDolceWindow.NAME, Class.new(TimeManagerDolceWindow, Gameplay._state.timeManager))
    Dolce.instance:addWindow(FamilyManagerDolceWindow.NAME, Class.new(FamilyManagerDolceWindow, Gameplay._state.familyManager))
end

---------------------------------------------------------------------------------
function Gameplay.removeDolceWindows()
    Dolce.instance:removeWindow(GameEventManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(CommandManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(MoneyManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(TimeManagerDolceWindow.NAME)
    Dolce.instance:removeWindow(FamilyManagerDolceWindow.NAME)
end

---------------------------------------------------------------------------------
Gameplay.REQUIRED_SOUNDS =
{
    path.combine("Audio", "Music", "KalimbaBreeze.wav"),
    path.combine("Audio", "SFX", "Birth.wav"),
    path.combine("Audio", "SFX", "ChildTrafficked.wav"),
    path.combine("Audio", "SFX", "Death.wav"),
    path.combine("Audio", "SFX", "Home.wav"),
    path.combine("Audio", "SFX", "Hospital.wav"),
    path.combine("Audio", "SFX", "Market.wav"),
    path.combine("Audio", "SFX", "Money.wav"),
    path.combine("Audio", "SFX", "Mosque.wav"),
    path.combine("Audio", "SFX", "School.wav"),
    path.combine("Audio", "SFX", "Well.wav"),
    path.combine("Audio", "SFX", "Work.wav"),
}

---------------------------------------------------------------------------------
Gameplay.REQUIRED_TEXTURES =
{
    path.combine("Textures", "UI", "LocationIcons", "Blank.png"),
    path.combine("Textures", "UI", "LocationIcons", "Farm.png"),
    path.combine("Textures", "UI", "LocationIcons", "Home.png"),
    path.combine("Textures", "UI", "LocationIcons", "Hospital.png"),
    path.combine("Textures", "UI", "LocationIcons", "Market.png"),
    path.combine("Textures", "UI", "LocationIcons", "Mosque.png"),
    path.combine("Textures", "UI", "LocationIcons", "School.png"),
    path.combine("Textures", "UI", "LocationIcons", "Well.png"),
    path.combine("Textures", "UI", "StatIcons", "Education.png"),
    path.combine("Textures", "UI", "StatIcons", "Happiness.png"),
    path.combine("Textures", "UI", "StatIcons", "Health.png"),
    path.combine("Textures", "UI", "StatIcons", "Safety.png"),
    path.combine("Textures", "UI", "Utility", "Bar.png"),
    path.combine("Textures", "UI", "Utility", "DialogBackground.png"),
    path.combine("Textures", "UI", "Utility", "Money.png"),
    path.combine("Textures", "UI", "Utility", "Time.png"),
    path.combine("Textures", "UI", "Utility", "TextBox.png"),
    path.combine("Textures", "UI", "Utility", "FamilyPanelBackground.png"),
    path.combine("Textures", "UI", "Utility", "MenuPanelBackground.png"),
    path.combine("Textures", "UI", "Utility", "MoneyPanelBackground.png"),
    path.combine("Textures", "UI", "Utility", "NotificationsBarBackground.png"),
    path.combine("Textures", "Village", "Background", "Background.png"),
    path.combine("Textures", "Village", "Background", "BoundaryLine.png"),
    path.combine("Textures", "Village", "Background", "MaliText.png"),
    path.combine("Textures", "Village", "Background", "TheIvoryCoastText.png"),
    path.combine("Textures", "Village", "Locations", "Decals", "CocoaTree.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "Home.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "Hospital.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "MarketFoodStalls.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "Mosque.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "School.png"),
    path.combine("Textures", "Village", "Locations", "Interactable", "Well.png"),
}

---------------------------------------------------------------------------------
Gameplay.REQUIRED_PREFABS =
{
    path.combine("Prefabs", "Gameplay", "Locations", "Farm.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "Home.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "Hospital.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "Market.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "Mosque.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "School.prefab"),
    path.combine("Prefabs", "Gameplay", "Locations", "Well.prefab"),
    path.combine("Prefabs", "UI", "Family", "ChildStatsPanel.prefab"),
    path.combine("Prefabs", "UI", "Family", "ChildIcon.prefab"),
    path.combine("Prefabs", "UI", "Family", "FamilyPanel.prefab"),
    path.combine("Prefabs", "UI", "Locations", "LocationDialog.prefab"),
    path.combine("Prefabs", "UI", "Menu", "InGameMenuDialog.prefab"),
    path.combine("Prefabs", "UI", "Money", "MoneyPanel.prefab"),
    path.combine("Prefabs", "UI", "Notifications", "NotificationDialog.prefab"),
    path.combine("Prefabs", "UI", "Notifications", "NotificationsPanel.prefab"),
    path.combine("Prefabs", "UI", "Time", "TimePanel.prefab"),
}

return Gameplay
