---------------------------------------------------------------------------------
local GameplayState =
{
    SAVE_DIRECTORY = path.combine(Resources.getResourcesDirectory(), "Data", "AppData", "Save"),
}

---------------------------------------------------------------------------------
function GameplayState:new(saveDirectory)
    if saveDirectory ~= nil then
        self.persistencePath = path.combine(saveDirectory, "Persistence.xml")
        self.timeManagerPath = path.combine(saveDirectory, "TimeManager.asset")
        self.moneyManagerPath = path.combine(saveDirectory, "MoneyManager.asset")
        self.familyManagerPath = path.combine(saveDirectory, "FamilyManager.asset")
        self.locationsManagerPath = path.combine(saveDirectory, "LocationsManager.asset")
        self.notificationManagerPath = path.combine(saveDirectory, "NotificationsManager.asset")
    else
        self.persistencePath = path.combine(Resources.getResourcesDirectory(), "Data", "Persistence", "Persistence.xml")
        self.timeManagerPath = path.combine(Resources.getResourcesDirectory(), "Data", "Time", "TimeManager.asset")
        self.moneyManagerPath = path.combine(Resources.getResourcesDirectory(), "Data", "Money", "MoneyManager.asset")
        self.familyManagerPath = path.combine(Resources.getResourcesDirectory(), "Data", "Family", "FamilyManager.asset")
        self.locationsManagerPath = path.combine(Resources.getResourcesDirectory(), "Data", "Locations", "LocationsManager.asset")
        self.notificationManagerPath = path.combine(Resources.getResourcesDirectory(), "Data", "Notifications", "NotificationsManager.asset")
    end
end

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