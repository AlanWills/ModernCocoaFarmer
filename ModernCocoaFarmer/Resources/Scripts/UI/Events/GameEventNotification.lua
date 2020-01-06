local Class = require 'OOP.Class'
local GameEventDialog = require 'UI.Events.GameEventDialog'

local GameEventNotification = 
{
    GAME_EVENT_NOTIFICATION_PREFAB_PATH = path.combine("Prefabs", "UI", "Events", "GameEventNotification.prefab")
}

---------------------------------------------------------------------------------
local function squelchNotification(eventArgs, caller)
    caller:die()
end

---------------------------------------------------------------------------------
local function showGameEventDialog(eventArgs, caller, self)
    squelchNotification(eventArgs, caller)

    Class.new(GameEventDialog, caller:getScreen(), self._gameEvent)
end

---------------------------------------------------------------------------------
function GameEventNotification:new(screen, gameEvent)
    self._gameEvent = gameEvent

    local notificationPrefab = Resources.loadPrefab(self.GAME_EVENT_NOTIFICATION_PREFAB_PATH)
    self.gameObject = notificationPrefab:instantiate(screen)
    local notificationInteractionHandler = self.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showGameEventDialog, self)
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(squelchNotification)
end

return GameEventNotification