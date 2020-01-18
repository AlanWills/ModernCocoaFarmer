local Class = require 'OOP.Class'
local csd = require "UI.Family.ChildStatsDialog"
local BuildingsUI = require 'UI.Buildings.BuildingsUI'
local TopBar = require "UI.TopBar"
local GameEventsBar = require 'UI.Events.GameEventsBar'

local GameplayScreen = 
{
    GAMEPLAY_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "Gameplay.screen"),
    TOP_BAR_NAME = "TopBarBackground",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    GAME_EVENTS_BAR_NAME = "GameEventsBar",
    BUILDINGS_UI_NAME = "BuildingsUI",
}

---------------------------------------------------------------------------------
local function onTimeChanged(eventArgs, deltaTime, timeManager)
    timeManager:update(deltaTime)
end

---------------------------------------------------------------------------------
local function applyFamilyManagerDailyModifiers(eventArgs, familyManager)
    familyManager:applyDailyModifiers()
end

---------------------------------------------------------------------------------
function GameplayScreen.show()
    -- Either caches instances or resources in memory to allow quicker prefab instancing
    csd.load()
    
    local timeManager = TimeManager.load(path.combine("Data", "Time", "TimeManager.asset"))
    local moneyManager = MoneyManager.load(path.combine("Data", "Money", "MoneyManager.asset"))
    local familyManager = FamilyManager.load(path.combine("Data", "Family", "FamilyManager.asset"))

    local buildingsManager = BuildingsManager.load(path.combine("Data", "Buildings", "BuildingsManager.asset"))
    buildingsManager:setTimeManager(timeManager)

    local gameEventManager = GameEventManager.load(path.combine("Data", "Events", "GameEventManager.asset"))
    gameEventManager:setTimeManager(timeManager)
    gameEventManager:setMoneyManager(moneyManager)
    gameEventManager:setFamilyManager(familyManager)
       
    familyManager:addChild()
    familyManager:addChild()
    timeManager:subscribeOnDayPassedCallback(applyFamilyManagerDailyModifiers, familyManager)
    
    local gameplayScreen = Screen.load(GameplayScreen.GAMEPLAY_SCREEN_PATH)
    
    local timeComponent = gameplayScreen:findGameObject(GameplayScreen.TIME_NOTIFIER_NAME):findComponent("TimeNotifier")
    timeComponent:subscribeOnTimeChangedCallback(onTimeChanged, timeManager)

    local buildingsUI = gameplayScreen:findGameObject(GameplayScreen.BUILDINGS_UI_NAME)
    GameplayScreen._buildingsUI = Class.new(BuildingsUI, buildingsManager, familyManager, buildingsUI)

    local topBarGameObject = gameplayScreen:findGameObject(GameplayScreen.TOP_BAR_NAME)
    GameplayScreen._topBar = Class.new(
        TopBar, 
        topBarGameObject, 
        familyManager, 
        moneyManager,
        timeManager)
      
    local gameEventsBar = gameplayScreen:findGameObject(GameplayScreen.GAME_EVENTS_BAR_NAME)
    GameplayScreen._gameEventsBar = Class.new(GameEventsBar, gameEventsBar, gameEventManager)

    GameplayScreen._timeManager = timeManager
    GameplayScreen._moneyManager = moneyManager
    GameplayScreen._familyManager = familyManager
    GameplayScreen._buildingsManager = buildingsManager
    GameplayScreen._gameEventManager = gameEventManager
end

return GameplayScreen