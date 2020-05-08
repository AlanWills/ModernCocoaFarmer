local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local UpdateChildrenTimesCommand = require 'Commands.Family.UpdateChildrenTimes'

local UpdateChildrenTimes = {}

---------------------------------------------------------------------------------
UpdateChildrenTimes.NAME = "UpdateChildrenTimes"
UpdateChildrenTimes.PERIOD = GameEventPeriod.EVERY_FRAME

---------------------------------------------------------------------------------
function UpdateChildrenTimes.trigger(commandManager, elapsedWorldTime)
    assert(UpdateChildrenTimesCommand ~= nil)
    commandManager:execute(UpdateChildrenTimesCommand, elapsedWorldTime)
end

return UpdateChildrenTimes