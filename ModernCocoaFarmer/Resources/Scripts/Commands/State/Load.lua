local GameplayState = require 'State.GameplayState'
local Class = require 'OOP.Class'

local Load = {}

---------------------------------------------------------------------------------
function Load:new(saveDirectory)
    self._saveDirectory = saveDirectory
end

---------------------------------------------------------------------------------
function Load:execute()
    local gameplayState = Class.new(GameplayState)
    gameplayState.persistencePath = path.combine(self._saveDirectory, "Persistence.xml")
    gameplayState.timeManagerPath = path.combine(self._saveDirectory, "TimeManager.asset")
    gameplayState.moneyManagerPath = path.combine(self._saveDirectory, "MoneyManager.asset")
    gameplayState.familyManagerPath = path.combine(self._saveDirectory, "FamilyManager.asset")
    gameplayState.locationsManagerPath = path.combine(self._saveDirectory, "LocationsManager.asset")
    gameplayState.notificationManagerPath = path.combine(self._saveDirectory, "NotificationsManager.asset")
    gameplayState:load()

    local gameplayScene = require "Scenes.Gameplay"
    gameplayScene.show(gameplayState)
end

return Load