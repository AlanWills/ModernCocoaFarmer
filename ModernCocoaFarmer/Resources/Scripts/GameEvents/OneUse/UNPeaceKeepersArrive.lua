local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local SendNotification = require 'Commands.Notifications.SendNotification'

local UNPeaceKeepersArrive = {}

---------------------------------------------------------------------------------
UNPeaceKeepersArrive.NAME = "UNPeaceKeepersArrive"
UNPeaceKeepersArrive.CHILD_SAFETY_THRESHOLD = 0
UNPeaceKeepersArrive.PERIOD = GameEventPeriod.EVERY_DAY
UNPeaceKeepersArrive.DATA_STORE_KEY = "UNPeaceKeepersArrivedOccurred"
UNPeaceKeepersArrive.ICON_PATH = path.combine("Textures", "Icons", "Events", "UNPeacekeepers.png")

---------------------------------------------------------------------------------
function UNPeaceKeepersArrive.canTrigger(commandManager)
    -- Check we haven't already triggered this
    if commandManager.persistence:getBool(UNPeaceKeepersArrive.DATA_STORE_KEY, false) then
        log("UNPeaceKeepersArrive already triggered")
        return false
    end

    -- Check at least one child has a safety less than or equal to the threshold
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:getSafety() <= UNPeaceKeepersArrive.CHILD_SAFETY_THRESHOLD then
            return true
        end
    end

    return false
end

---------------------------------------------------------------------------------
function UNPeaceKeepersArrive.trigger(commandManager)
    -- Make sure to save that this event has been triggered
    commandManager.persistence:setBool(UNPeaceKeepersArrive.DATA_STORE_KEY, true)

    local modifier = Modifier.create("UNPeaceKeepersArrive Modifier")
    modifier:setAmount(100)
    modifier:setChangeType("Absolute")

    -- Set all children's safety to 100
    commandManager.familyManager:applySafetyModifier(modifier)

    commandManager:execute(
        SendNotification,
        "UN Peace Keepers Arrive",
        "UN Peacekeeping helps countries navigate the difficult path from conflict to peace",
        UNPeaceKeepersArrive.ICON_PATH)
end

return UNPeaceKeepersArrive