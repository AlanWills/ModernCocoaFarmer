local Class = require 'OOP.Class'
local Queue = require 'Containers.Queue'

local CommandManager = {}

---------------------------------------------------------------------------------
function CommandManager:new(commandManager)
    self._commandQueue = Class.new(Queue)
end

---------------------------------------------------------------------------------
function CommandManager:execute(commandType, ...)
    local command = Class.new(commandType, ...)
    self._commandQueue:push(command)
end

---------------------------------------------------------------------------------
function CommandManager:update()
    local queueToExecute = Class.new(Queue)

    while self._commandQueue:size() > 0 do
        queueToExecute:push(self._commandQueue:pop())
    end

    while queueToExecute:size() > 0 do
        queueToExecute:pop():execute(self)
    end
end

return CommandManager