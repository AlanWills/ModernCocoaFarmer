local Class = require 'OOP.Class'
local NotificationDialog = require 'UI.Notifications.NotificationDialog'

local NotificationIcon = 
{
    NOTIFICATION_ICON_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationIcon.prefab"),
    NOTIFICATION_ICON_NAME = "NotificationIcon"
}

---------------------------------------------------------------------------------
local function showNotificationDialogCallback(caller, self)
    self:showNotificationDialog()
end

---------------------------------------------------------------------------------
function NotificationIcon:new(notification, parent)
    self._title = notification:getName()
    self._description = notification:getDescription()

    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    self.gameObject = notificationPrefab:instantiate()

    local notificationInteractionHandler = self.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showNotificationDialogCallback, self)

    local notificationIcon = self.gameObject:findChild(self.NOTIFICATION_ICON_NAME)
    notificationIcon:findComponent("SpriteRenderer"):setTexture(notification:getIcon())
end

---------------------------------------------------------------------------------
function NotificationIcon:showNotificationDialog()
    Class.new(NotificationDialog, self._title, self._description)
end

return NotificationIcon