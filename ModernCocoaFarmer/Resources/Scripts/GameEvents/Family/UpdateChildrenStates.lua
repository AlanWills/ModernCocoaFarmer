local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local UpdateChildrenStatesCommand = require 'Commands.Family.UpdateChildrenStates'

local UpdateChildrenStates = {}

---------------------------------------------------------------------------------
UpdateChildrenStates.NAME = "UpdateChildrenStates"
UpdateChildrenStates.PERIOD = GameEventPeriod.EVERY_DAY

---------------------------------------------------------------------------------
function UpdateChildrenStates.trigger(commandManager)
    commandManager:execute(UpdateChildrenStatesCommand)
end

return UpdateChildrenStates