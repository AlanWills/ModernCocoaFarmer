local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddChild = require 'Commands.Family.AddChild'
local SendNotification = require 'Commands.Notifications.SendNotification'
local FamilyUtils = require 'Utility.FamilyUtils'

local TryAddChild = {}

---------------------------------------------------------------------------------
TryAddChild.NAME = "TryAddChild"
TryAddChild.PERIOD = GameEventPeriod.EVERY_MONTH
TryAddChild.YEARLY_PERIOD = 1
TryAddChild.MONTH_TO_TRIGGER = 2
TryAddChild.BASE_PROBABILITY = 0.4
TryAddChild.ICON_PATH = path.combine("Textures", "Icons", "Events", "ChildBorn.png")

---------------------------------------------------------------------------------
function TryAddChild.canTrigger(commandManager)
    local familyManager = commandManager.familyManager
    local timeManager = commandManager.timeManager

    if not familyManager:canAddChild() then
        return false
    end

    local correctTimeToTrigger = ((timeManager:getCurrentYear() % TryAddChild.YEARLY_PERIOD) == 0) and 
                                  (timeManager:getCurrentMonth() == TryAddChild.MONTH_TO_TRIGGER)
    log("TryAddChild correctTimeToTrigger: " .. tostring(correctTimeToTrigger))

    if not correctTimeToTrigger then
        return false
    end

    local numActiveChildren = FamilyUtils.getActivatedChildCount(familyManager)
    if numActiveChildren == 1 then
        return true
    end

    local probability = TryAddChild.BASE_PROBABILITY + (1 - TryAddChild.BASE_PROBABILITY) * (familyManager:getChildCount() - numActiveChildren - 1) / (familyManager:getChildCount() - 2)
    
    log("TryAddChild probability: " .. tostring(probability))
    assert(probability <= 1)
    assert(probability >= TryAddChild.BASE_PROBABILITY)

    return probability >= math.random()
end

---------------------------------------------------------------------------------
function TryAddChild.trigger(commandManager)
    commandManager:execute(AddChild)

    local familyManager = commandManager.familyManager
    local child = FamilyUtils.getFirstNotBornChild(familyManager)
    assert(child ~= nil)

    commandManager:execute(
        SendNotification,
        "A Child!",
        "You welcome " .. child:getName() .. " as the newest member of the family",
        TryAddChild.ICON_PATH)
end

return TryAddChild