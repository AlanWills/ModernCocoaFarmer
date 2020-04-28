local Save = {}

---------------------------------------------------------------------------------
function Save:new(saveDirectory)
    self._saveDirectory = saveDirectory
end

---------------------------------------------------------------------------------
function Save:execute(commandManager)
    local saveDirectory = Directory.new(self._saveDirectory)
    if not saveDirectory:exists() then
        saveDirectory:create()
    end

    commandManager.timeManager:save(path.combine(self._saveDirectory, "TimeManager.asset"))
    commandManager.moneyManager:save(path.combine(self._saveDirectory, "MoneyManager.asset"))
    commandManager.familyManager:save(path.combine(self._saveDirectory, "FamilyManager.asset"))
    commandManager.locationsManager:save(path.combine(self._saveDirectory, "LocationsManager.asset"))
    commandManager.notificationManager:save(path.combine(self._saveDirectory, "NotificationsManager.asset"))

    log("Game saved successfully in " .. self._saveDirectory)
end

return Save