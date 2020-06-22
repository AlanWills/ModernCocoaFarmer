local SendNotification = require 'Commands.Notifications.SendNotification'

---------------------------------------------------------------------------------
local GraduateChild =
{
    ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildGraduated.png"),
    SFX_PATH = path.combine("Audio", "SFX", "Notification.wav"),  -- Replace
}

---------------------------------------------------------------------------------
function GraduateChild:new(childName)
    self._childName = childName
end

---------------------------------------------------------------------------------
function GraduateChild:execute(commandManager)
    local child = commandManager.familyManager:findChild(self._childName)

    if child == nil then
        log("[GraduateChild]  Could not find child " .. self._childName)
        return
    end

    log("Graduating child " .. self._childName)
    child:die()

    commandManager:execute(
        SendNotification,
        "Graduation Day!",
        "School is never easy, but " .. self._childName .. " has successfully graduated.  Their education gives them hope for a better life.",
        GraduateChild.ICON_PATH,
        GraduateChild.SFX_PATH)
end

---------------------------------------------------------------------------------
function GraduateChild.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    return args
end

return GraduateChild