local Class = require 'OOP.Class'

local CommandManager = {}

---------------------------------------------------------------------------------
function CommandManager:new(state)
    self.persistence = state.persistence
    self.timeManager = state.timeManager
    self.moneyManager = state.moneyManager
    self.familyManager = state.familyManager
    self.locationsManager = state.locationsManager
    self.notificationManager = state.notificationManager
    self.modalDialogManager = state.modalDialogManager
end

---------------------------------------------------------------------------------
function CommandManager:execute(commandType, ...)
    local command = Class.new(commandType, ...)
    command:execute(self)
end

return CommandManager