local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local ApplyFamilyModifiersCommand = require 'Commands.Family.ApplyFamilyModifiers'

local ApplyFamilyModifiers = {}

---------------------------------------------------------------------------------
ApplyFamilyModifiers.NAME = "ApplyFamilyModifiers"
ApplyFamilyModifiers.PERIOD = GameEventPeriod.EVERY_DAY

---------------------------------------------------------------------------------
function ApplyFamilyModifiers.trigger(commandManager)
    commandManager:execute(ApplyFamilyModifiersCommand)
end

return ApplyFamilyModifiers