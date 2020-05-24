local GameplayStateConstants = require 'State.GameplayStateConstants'

local GameplayState = {}

---------------------------------------------------------------------------------
GameplayState.persistencePath = GameplayStateConstants.DEFAULT_PERSISTENCE_PATH
GameplayState.timeManagerPath = GameplayStateConstants.DEFAULT_TIME_MANAGER_PATH
GameplayState.moneyManagerPath = GameplayStateConstants.DEFAULT_MONEY_MANAGER_PATH
GameplayState.familyManagerPath = GameplayStateConstants.DEFAULT_FAMILY_MANAGER_PATH
GameplayState.locationsManagerPath = GameplayStateConstants.DEFAULT_LOCATIONS_MANAGER_PATH
GameplayState.notificationManagerPath = GameplayStateConstants.DEFAULT_NOTIFICATION_MANAGER_PATH

---------------------------------------------------------------------------------
function GameplayState:load()
    self.persistence = DataStore.loadOrCreate(self.persistencePath)
    self.timeManager = TimeManager.load(self.timeManagerPath)
    self.moneyManager = MoneyManager.load(self.moneyManagerPath)
    self.familyManager = FamilyManager.load(self.familyManagerPath)
    self.locationsManager = LocationsManager.load(self.locationsManagerPath)
    self.notificationManager = NotificationManager.load(self.notificationManagerPath)

    local dataSystem = System.getDataSystem()

    self.timeManager:setDataSystem(dataSystem)
    self.moneyManager:setDataSystem(dataSystem)
    self.familyManager:setDataSystem(dataSystem)
    self.locationsManager:setDataSystem(dataSystem)
end

return GameplayState