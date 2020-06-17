local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local LeaveChild = require 'Commands.Locations.LeaveChild'
local SendNotification = require 'Commands.Notifications.SendNotification'
local AddMoney = require 'Commands.Money.AddMoney'

---------------------------------------------------------------------------------
local CheckForChildrenLeaving = {}
CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildDead.png")
CheckForChildrenLeaving.CHILD_PAID_ICON_PATH = path.combine("Textures", "UI", "Utility", "Money.png")
CheckForChildrenLeaving.NAME = "CheckForChildrenLeaving"
CheckForChildrenLeaving.PERIOD = GameEventPeriod.EVERY_DAY
CheckForChildrenLeaving.SALARY = 9740

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.trigger(commandManager)
    local locationsManager = commandManager.locationsManager
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            local location = locationsManager:findLocation(child:getCurrentLocation())

            if child:getTimeAtLocation() >= location:getDaysToComplete() then
                commandManager:execute(LeaveChild, child:getCurrentLocation(), child:getName())

                local locationName = location:getName()

                if locationName == "Farm" then
                    CheckForChildrenLeaving.handleLeavingFarm(commandManager, child)
                elseif locationName == "Home" then
                    CheckForChildrenLeaving.handleChildLeavingHome(commandManager, child)
                elseif locationName == "Hospital" then
                    CheckForChildrenLeaving.handleChildLeavingHospital(commandManager, child)
                elseif locationName == "Market" then
                    CheckForChildrenLeaving.handleChildLeavingMarket(commandManager, child)
                elseif locationName == "Mosque" then
                    CheckForChildrenLeaving.handleChildLeavingMosque(commandManager, child)
                elseif locationName == "School" then
                    CheckForChildrenLeaving.handleChildLeavingSchool(commandManager, child)
                elseif locationName == "Well" then
                    CheckForChildrenLeaving.handleChildLeavingWell(commandManager, child)
                end
            end
        end
    end
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingFarm(commandManager, child)
    if math.random() > child:getSafety() then
        -- Child is trafficked
        child:die()

        commandManager:execute(
            SendNotification,
            "Child Trafficked...",
            "The unthinkable has happened.  On the return journey from the Cocoa Farm " .. child:getName() .. " was taken.  You pray you will see them again, but deep down you know you won't.",
            CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH)
    else
        commandManager:execute(AddMoney, CheckForChildrenLeaving.SALARY)

        commandManager:execute(
            SendNotification,
            "Child Paid",
            "After a bitter month's work, " .. child:getName() .. " has been paid " .. tostring(CheckForChildrenLeaving.SALARY) .. ".",
            CheckForChildrenLeaving.CHILD_PAID_ICON_PATH)
    end
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingHome(commandManager, child)
    commandManager:execute(
        SendNotification,
        "Home Chores Complete",
        "The errands " .. child:getName() .. " has done may not change the world, but will make it more bearable."
        "")
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingHospital(commandManager, child)
    commandManager:execute(
        SendNotification,
        "Hospital Visit Complete",
        "Fully recovered from their ailments, " .. child:getName() .. " heads for home.",
        "")
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingMarket(commandManager, child)
    commandManager:execute(
        SendNotification,
        "Market Visit Complete",
        child:getName() .. " has brought back all manner of food from the market.",
        "")
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingMosque(commandManager, child)
    commandManager:execute(
        SendNotification,
        "Mosque Visit Complete",
        "Inspired and with a little more understanding of the world, " .. child:getName() .. " is ready to take it head on.",
        "")
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingSchool(commandManager, child)
    commandManager:execute(
        SendNotification,
        "School Visit Complete",
        "Facts and figures all add up.  Some day, " .. child:getName() .. " will put them to incredible use.",
        "")
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingWell(commandManager, child)
    commandManager:execute(
        SendNotification,
        "Well Visit Complete",
        "Carrying water is tough.  " .. child:getName() .. "knows it's worth it.",
        "")
end

return CheckForChildrenLeaving