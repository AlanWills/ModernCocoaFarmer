local GameplayState = require 'State.GameplayState'
local Class = require 'OOP.Class'

local LoadGameplayCommand = {}

---------------------------------------------------------------------------------
function LoadGameplayCommand:new(saveDirectory)
    self._saveDirectory = saveDirectory
end

---------------------------------------------------------------------------------
function LoadGameplayCommand:execute()
    local gameplayState = Class.new(GameplayState)
    gameplayState.timeManagerPath = path.combine(self._saveDirectory, "TimeManager.asset")
    gameplayState.moneyManagerPath = path.combine(self._saveDirectory, "MoneyManager.asset")
    gameplayState.familyManagerPath = path.combine(self._saveDirectory, "FamilyManager.asset")
    gameplayState.locationsManagerPath = path.combine(self._saveDirectory, "LocationsManager.asset")
    gameplayState.notificationManagerPath = path.combine(self._saveDirectory, "NotificationsManager.asset")
    gameplayState:load()

    local gameplayScene = require "Scenes.Gameplay"
    gameplayScene.show(gameplayState)
end

return LoadGameplayCommand