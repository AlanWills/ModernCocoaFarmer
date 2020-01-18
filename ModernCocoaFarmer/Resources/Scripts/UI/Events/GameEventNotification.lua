local Class = require 'OOP.Class'
local GameEventDialog = require 'UI.Events.GameEventDialog'

local GameEventNotification = 
{
    GAME_EVENT_NOTIFICATION_PREFAB_PATH = path.combine("Prefabs", "UI", "Events", "GameEventNotification.prefab"),
    GAME_EVENT_NOTIFICATION_ICON_NAME = "EventNotificationIcon"
}

---------------------------------------------------------------------------------
local function showGameEventDialogCallback(eventArgs, caller, self)
    self:showGameEventDialog(caller:getScreen())
end

---------------------------------------------------------------------------------
function GameEventNotification:new(gameEvent, parent)
    self.gameEvent = gameEvent

    local notificationPrefab = Resources.loadPrefab(self.GAME_EVENT_NOTIFICATION_PREFAB_PATH)
    self.gameObject = notificationPrefab:instantiate(parent:getScreen())

    local notificationInteractionHandler = self.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showGameEventDialogCallback, self)

    local notificationIcon = self.gameObject:findChildGameObject(self.GAME_EVENT_NOTIFICATION_ICON_NAME)
    notificationIcon:findComponent("SpriteRenderer"):setTexture(gameEvent:getIcon())
end

---------------------------------------------------------------------------------
function GameEventNotification:showGameEventDialog(screen)
    Class.new(GameEventDialog, screen, self.gameEvent)
end

return GameEventNotification