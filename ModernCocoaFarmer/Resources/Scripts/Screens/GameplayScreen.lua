local Class = require 'OOP.Class'
local LocationsUI = require 'UI.Locations.LocationsUI'
local TopBar = require "UI.TopBar"
local GameEventsBar = require 'UI.Events.GameEventsBar'

local GameplayScreen = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    GAME_EVENTS_BAR_NAME = "GameEventsBar",
    LOCATIONS_UI_NAME = "LocationsUI",
}

---------------------------------------------------------------------------------
local function onTimeChanged(eventArgs, deltaTime, timeManager)
    timeManager:update(deltaTime)
end

---------------------------------------------------------------------------------
function GameplayScreen.show()
    local timeManager = TimeManager.load(path.combine("Data", "Time", "TimeManager.asset"))
    local moneyManager = MoneyManager.load(path.combine("Data", "Money", "MoneyManager.asset"))
    local familyManager = FamilyManager.load(path.combine("Data", "Family", "FamilyManager.asset"))
    local locationsManager = LocationsManager.load(path.combine("Data", "Locations", "LocationsManager.asset"))

    local gameEventManager = GameEventManager.load(path.combine("Data", "Events", "GameEventManager.asset"))
    gameEventManager:setTimeManager(timeManager)
    gameEventManager:setMoneyManager(moneyManager)
    gameEventManager:setFamilyManager(familyManager)
    gameEventManager:setLocationsManager(locationsManager)
       
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
        timeManager,
        gameEventManager)
    GameplayScreen._topBar:updateUI()
      
    local gameEventsBar = gameplayScreen:findGameObject(GameplayScreen.GAME_EVENTS_BAR_NAME)
    GameplayScreen._gameEventsBar = Class.new(GameEventsBar, gameEventsBar, gameEventManager)

    GameplayScreen._timeManager = timeManager
    GameplayScreen._moneyManager = moneyManager
    GameplayScreen._familyManager = familyManager
    GameplayScreen._locationsManager = locationsManager
    GameplayScreen._gameEventManager = gameEventManager
end

return GameplayScreen