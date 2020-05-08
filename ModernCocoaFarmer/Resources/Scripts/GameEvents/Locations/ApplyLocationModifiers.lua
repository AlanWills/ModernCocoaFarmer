local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local ApplyLocationModifiersCommand = require 'Commands.Locations.ApplyLocationModifiers'

local ApplyLocationModifiers = {}

---------------------------------------------------------------------------------
ApplyLocationModifiers.NAME = "ApplyLocationModifiers"
ApplyLocationModifiers.PERIOD = GameEventPeriod.EVERY_DAY

---------------------------------------------------------------------------------
function ApplyLocationModifiers.trigger(commandManager)
    commandManager:execute(ApplyLocationModifiersCommand)
end

return ApplyLocationModifiers