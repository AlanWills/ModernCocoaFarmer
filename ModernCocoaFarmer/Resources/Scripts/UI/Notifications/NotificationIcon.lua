local Class = require 'OOP.Class'
local NotificationDialog = require 'UI.Notifications.NotificationDialog'

local NotificationIcon = 
{
    NOTIFICATION_ICON_NAME = "NotificationIcon"
}

---------------------------------------------------------------------------------
local function showNotificationDialogCallback(caller, self)
    self:showNotificationDialog()
end

---------------------------------------------------------------------------------
function NotificationIcon:new(notification, gameObject)
    self._title = notification:getName()
    self._description = notification:getDescription()
    self._gameObject = gameObject

    local notificationInteractionHandler = gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showNotificationDialogCallback, self)

    local notificationIcon = gameObject:findChild(self.NOTIFICATION_ICON_NAME)
    notificationIcon:findComponent("SpriteRenderer"):setTexture(notification:getIcon())
end

---------------------------------------------------------------------------------
function NotificationIcon:showNotificationDialog()
    Class.new(NotificationDialog, self._title, self._description)
end

return NotificationIcon