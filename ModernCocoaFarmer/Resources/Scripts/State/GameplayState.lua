local GameplayStateConstants = require 'State.GameplayStateConstants'

local GameplayState = {}

---------------------------------------------------------------------------------
GameplayState.timeManagerPath = GameplayStateConstants.DEFAULT_TIME_MANAGER_PATH
GameplayState.moneyManagerPath = GameplayStateConstants.DEFAULT_MONEY_MANAGER_PATH
GameplayState.familyManagerPath = GameplayStateConstants.DEFAULT_FAMILY_MANAGER_PATH
GameplayState.locationsManagerPath = GameplayStateConstants.DEFAULT_LOCATIONS_MANAGER_PATH
GameplayState.notificationManagerPath = GameplayStateConstants.DEFAULT_NOTIFICATION_MANAGER_PATH
GameplayState.gameEventManagerPath = GameplayStateConstants.DEFAULT_GAME_EVENT_MANAGER_PATH

---------------------------------------------------------------------------------
function GameplayState:load()
    self.dataStore = DataStore.create()
    self.timeManager = TimeManager.load(self.timeManagerPath)
    self.moneyManager = MoneyManager.load(self.moneyManagerPath)
    self.familyManager = FamilyManager.load(self.familyManagerPath)
    self.locationsManager = LocationsManager.load(self.locationsManagerPath)
    self.notificationManager = NotificationManager.load(self.notificationManagerPath)
    self.gameEventManager = GameEventManager.load(self.gameEventManagerPath)

    self.timeManager:setDataStore(self.dataStore)
    self.moneyManager:setDataStore(self.dataStore)
    self.familyManager:setDataStore(self.dataStore)
    self.locationsManager:setDataStore(self.dataStore)

    self.gameEventManager:setTimeManager(self.timeManager)
    self.gameEventManager:setMoneyManager(self.moneyManager)
    self.gameEventManager:setFamilyManager(self.familyManager)
    self.gameEventManager:setLocationsManager(self.locationsManager)
    self.gameEventManager:setNotificationManager(self.notificationManager)
end

return GameplayState