local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local LeaveChild = require 'Commands.Locations.LeaveChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

---------------------------------------------------------------------------------
local CheckForChildrenLeaving = {}
CheckForChildrenLeaving.MIN_HAPPINESS_FOR_EXPULSION = 40
CheckForChildrenLeaving.MIN_SAFETY_FOR_TRAFFICKING = 40
CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildDead.png")
CheckForChildrenLeaving.CHILD_TRAFFICKED_SFX_PATH = path.combine("Audio", "SFX", "ChildTrafficked.wav")
CheckForChildrenLeaving.CHILD_EXPELLED_ICON_PATH = path.combine("Textures", "Icons", "Events", "ChildExpelled.png")
CheckForChildrenLeaving.CHILD_EXPELLED_SFX_PATH = path.combine("Audio", "SFX", "ChildExpelled.wav")
CheckForChildrenLeaving.CHILD_PAID_ICON_PATH = path.combine("Textures", "UI", "Utility", "Money.png")
CheckForChildrenLeaving.CHILD_PAID_SFX_PATH = path.combine("Audio", "SFX", "Money.wav")
CheckForChildrenLeaving.NAME = "CheckForChildrenLeaving"
CheckForChildrenLeaving.PERIOD = GameEventPeriod.EVERY_DAY

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
                    CheckForChildrenLeaving.handleLeavingFarm(commandManager, child, location)
                elseif locationName == "Home" then
                    CheckForChildrenLeaving.handleLeavingHome(commandManager, child, location)
                elseif locationName == "Hospital" then
                    CheckForChildrenLeaving.handleLeavingHospital(commandManager, child, location)
                elseif locationName == "Market" then
                    CheckForChildrenLeaving.handleLeavingMarket(commandManager, child, location)
                elseif locationName == "Mosque" then
                    CheckForChildrenLeaving.handleLeavingMosque(commandManager, child, location)
                elseif locationName == "School" then
                    CheckForChildrenLeaving.handleLeavingSchool(commandManager, child, location)
                elseif locationName == "Well" then
                    CheckForChildrenLeaving.handleLeavingWell(commandManager, child, location)
                end
            end
        end
    end
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingFarm(commandManager, child, location)
    local randomCheck = math.random(0, CheckForChildrenLeaving.MIN_SAFETY_FOR_TRAFFICKING)
    log(string.format("Farm randomCheck %f", randomCheck))
    log(string.format("%s safety %f", child:getName(), child:getSafety()))

    if randomCheck > child:getSafety() then
        -- Child is trafficked
        child:die()

        commandManager:execute(
            SendNotification,
            "Child Trafficked...",
            "The unthinkable has happened.  On the return journey from the Cocoa Farm " .. child:getName() .. " was taken.  You pray you will see them again, but deep down you know you won't.",
            CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH,
            CheckForChildrenLeaving.CHILD_TRAFFICKED_SFX_PATH)
    else
        commandManager:execute(
            SendNotification,
            "Work Complete",
            string.format("After a bitter month's work, %s has been paid %d.", child:getName(), location:getMoneyModifier():getAmount()),
            CheckForChildrenLeaving.CHILD_PAID_ICON_PATH,
            CheckForChildrenLeaving.CHILD_PAID_SFX_PATH)
    end
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingHome(commandManager, child, location)
    commandManager:execute(
        SendNotification,
        "Home Chores Complete",
        "The errands " .. child:getName() .. " has done may not change the world, but will make it more bearable.",
        location:getIcon(),
        location:getSfx())
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingHospital(commandManager, child, location)
    commandManager:execute(
        SendNotification,
        "Hospital Visit Complete",
        "Fully recovered from their ailments, " .. child:getName() .. " heads for home.",
        location:getIcon(),
        location:getSfx())
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingMarket(commandManager, child, location)
    commandManager:execute(
        SendNotification,
        "Market Visit Complete",
        child:getName() .. " has brought back all manner of food from the market.",
        location:getIcon(),
        location:getSfx())
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingMosque(commandManager, child, location)
    commandManager:execute(
        SendNotification,
        "Mosque Visit Complete",
        "Inspired and with a little more understanding of the world, " .. child:getName() .. " is ready to take it head on.",
        location:getIcon(),
        location:getSfx())
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingSchool(commandManager, child, location)
    local randomCheck = math.random(0, CheckForChildrenLeaving.MIN_HAPPINESS_FOR_EXPULSION)
    log(string.format("School randomCheck %f", randomCheck))
    log(string.format("%s happiness %f", child:getName(), child:getHappiness()))
    
    if randomCheck > child:getHappiness() then
        child:setEducation(child:getEducation() * 0.5)

        commandManager:execute(
            SendNotification,
            "Child Expelled...",
            "Bitter with life, " .. child:getName() .. " has caused serious trouble at school and been told to leave.",
            CheckForChildrenLeaving.CHILD_EXPELLED_ICON_PATH,
            CheckForChildrenLeaving.CHILD_EXPELLED_SFX_PATH)
    else
        commandManager:execute(
            SendNotification,
            "School Visit Complete",
            "Facts and figures all add up.  Some day, " .. child:getName() .. " will put them to incredible use.",
            location:getIcon(),
            location:getSfx())
    end
end

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.handleLeavingWell(commandManager, child, location)
    commandManager:execute(
        SendNotification,
        "Well Visit Complete",
        "Carrying water is tough.  " .. child:getName() .. "knows it's worth it.",
        location:getIcon(),
        location:getSfx())
end

return CheckForChildrenLeaving