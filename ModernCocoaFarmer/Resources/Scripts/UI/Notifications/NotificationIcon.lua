local Class = require 'OOP.Class'
local NotificationDialog = require 'UI.Notifications.NotificationDialog'

local NotificationIcon = 
{
    NOTIFICATION_ICON_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationIcon.prefab"),
    NOTIFICATION_ICON_NAME = "NotificationIcon"
}

---------------------------------------------------------------------------------
local function showNotificationDialogCallback(eventArgs, caller, self)
    self:showNotificationDialog(caller:getScreen())
end

---------------------------------------------------------------------------------
function NotificationIcon:new(notification, parent)
    self.notification = notification

    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    self.gameObject = notificationPrefab:instantiate(parent:getScreen())

    local notificationInteractionHandler = self.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showNotificationDialogCallback, self)

    local notificationIcon = self.gameObject:findChildGameObject(self.NOTIFICATION_ICON_NAME)
    notificationIcon:findComponent("SpriteRenderer"):setTexture(notification:getIcon())
end

---------------------------------------------------------------------------------
function NotificationIcon:showNotificationDialog(screen)
    Class.new(NotificationDialog, screen, self.notification)
end

return NotificationIcon