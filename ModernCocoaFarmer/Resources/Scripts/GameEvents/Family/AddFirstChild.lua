local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddChild = require 'Commands.Family.AddChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

local ActivateFirstChild = {}

---------------------------------------------------------------------------------
ActivateFirstChild.NAME = "ActivateFirstChild"
ActivateFirstChild.PERIOD = GameEventPeriod.EVERY_DAY
ActivateFirstChild.DAY_TO_TRIGGER = 20
ActivateFirstChild.MONTH_TO_TRIGGER = 0
ActivateFirstChild.YEAR_TO_TRIGGER = 0
ActivateFirstChild.ICON_PATH = path.combine("Textures", "Icons", "Events", "ChildBorn.png")

---------------------------------------------------------------------------------
function ActivateFirstChild.canTrigger(commandManager)
    local timeManager = commandManager.timeManager

    return timeManager:getCurrentDay() == ActivateFirstChild.DAY_TO_TRIGGER and
           timeManager:getCurrentMonth() == ActivateFirstChild.MONTH_TO_TRIGGER and
           timeManager:getCurrentYear() == ActivateFirstChild.YEAR_TO_TRIGGER
end

---------------------------------------------------------------------------------
function ActivateFirstChild.trigger(commandManager)
    commandManager:execute(AddChild)

    local familyManager = commandManager.familyManager
    local child = familyManager:getChild(familyManager:getChildCount() - 1)

    commandManager:execute(
        SendNotification,
        "A Child!",
        "You welcome " .. child:getName() .. " as the newest member of the family",
        ActivateFirstChild.ICON_PATH)
end

return ActivateFirstChild