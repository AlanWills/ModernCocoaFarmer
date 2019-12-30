local Class = require 'OOP.Class'

local EventNotification = 
{
    EVENT_NOTIFICATION_PREFAB_PATH = path.combine("Prefabs", "UI", "Events", "EventNotification.prefab")
}

---------------------------------------------------------------------------------
local function squelchNotification(eventArgs, caller)
    caller:die()
end

---------------------------------------------------------------------------------
local function showEventDialog(eventArgs, caller, self)
    squelchNotification(eventArgs, caller)

    local EventDialog = require 'UI.Events.EventDialog'
    Class.new(EventDialog, caller:getScreen(), self._gameEvent)
end

---------------------------------------------------------------------------------
function EventNotification:new(screen, gameEvent)
    self._gameEvent = gameEvent

    local notificationPrefab = Resources.loadPrefab(self.EVENT_NOTIFICATION_PREFAB_PATH)
    local notificationInstance = notificationPrefab:instantiate(screen)
    local notificationInteractionHandler = notificationInstance:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showEventDialog, self)
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(squelchNotification)
end