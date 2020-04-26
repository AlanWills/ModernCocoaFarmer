local Class = require 'OOP.Class'
local Queue = require 'Containers.Queue'

local CommandManager = {}

---------------------------------------------------------------------------------
function CommandManager:new(state)
    self._commandQueue = Class.new(Queue)
    self.timeManager = state.timeManager
    self.moneyManager = state.moneyManager
    self.familyManager = state.familyManager
    self.locationsManager = state.locationsManager
    self.notificationManager = state.notificationManager
    self.gameEventManager = state.gameEventManager
    self.modalDialogManager = state.modalDialogManager
end

---------------------------------------------------------------------------------
function CommandManager:execute(commandType, ...)
    local command = Class.new(commandType, ...)
    self._commandQueue:push(command)
end

---------------------------------------------------------------------------------
function CommandManager:update()
    while self._commandQueue:size() > 0 do
        self._commandQueue:pop():execute(self)
    end
end

return CommandManager