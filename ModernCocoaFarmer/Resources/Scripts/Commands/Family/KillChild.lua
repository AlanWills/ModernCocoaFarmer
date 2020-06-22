local SendNotification = require 'Commands.Notifications.SendNotification'

---------------------------------------------------------------------------------
local KillChild =
{
    ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildDead.png"),
    SFX_PATH = path.combine("Audio", "SFX", "Death.wav"),
}

---------------------------------------------------------------------------------
function KillChild:new(childName)
    self._childName = childName
end

---------------------------------------------------------------------------------
function KillChild:execute(commandManager)
    local child = commandManager.familyManager:findChild(self._childName)

    if child == nil then
        log("[KillChild]  Could not find child " .. self._childName)
        return
    end

    log("Killing child " .. self._childName)
    child:die()

    commandManager:execute(
        SendNotification,
        "A Child Dies...",
        "After lingering on death's door, " .. self._childName .. " has finally stepped over.  Your family bitterly rues their passing.",
        KillChild.ICON_PATH)
end

---------------------------------------------------------------------------------
function KillChild.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    return args
end

return KillChild