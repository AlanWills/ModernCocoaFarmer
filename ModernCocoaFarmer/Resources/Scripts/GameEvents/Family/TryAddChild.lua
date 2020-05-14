local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddChild = require 'Commands.Family.AddChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

local TryAddChild = {}

---------------------------------------------------------------------------------
TryAddChild.NAME = "TryAddChild"
TryAddChild.PERIOD = GameEventPeriod.EVERY_YEAR
TryAddChild.YEARLY_PERIOD = 2
TryAddChild.PROBABILITY = 0.5
TryAddChild.ICON_PATH = path.combine("Textures", "Icons", "Events", "ChildBorn.png")

---------------------------------------------------------------------------------
function TryAddChild.canTrigger(commandManager)
    local familyManager = commandManager.familyManager
    local timeManager = commandManager.timeManager

    if not familyManager:canAddChild() then
        return false
    end

    local correctTimeToTrigger = (timeManager:getCurrentYear() % TryAddChild.YEARLY_PERIOD) == 0
    return correctTimeToTrigger and TryAddChild.PROBABILITY >= math.random()
end

---------------------------------------------------------------------------------
function TryAddChild.trigger(commandManager)
    commandManager:execute(AddChild)

    local familyManager = commandManager.familyManager
    local child = nil

    -- No need to check the 0th child as it's activated in a different event
    for childIndex = familyManager:getChildCount() - 1, 1, -1 do
        local currentChild = familyManager:getChild(childIndex)
        if currentChild:isActive() then
            child = currentChild
        end
    end

    assert(child ~= nil)
    commandManager:execute(
        SendNotification,
        "A Child!",
        "You welcome " .. child:getName() .. " as the newest member of the family",
        TryAddChild.ICON_PATH)
end

return TryAddChild