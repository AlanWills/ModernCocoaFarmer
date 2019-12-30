local Class = require 'OOP.Class'
local EventDialog = require 'UI.Events.EventDialog'

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

    Class.new(EventDialog, caller:getScreen(), self._gameEvent)
end

---------------------------------------------------------------------------------
function EventNotification:new(screen, gameEvent)
    self._gameEvent = gameEvent

    local notificationPrefab = Resources.loadPrefab(self.EVENT_NOTIFICATION_PREFAB_PATH)
    self.gameObject = notificationPrefab:instantiate(screen)
    local notificationInteractionHandler = self.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showEventDialog, self)
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(squelchNotification)
end

return EventNotification