local Class = require 'OOP.Class'
local NotificationUtils = require 'Utility.NotificationUtils'

local NotificationIcon = {}

---------------------------------------------------------------------------------
function NotificationIcon.showNotificationDialogCallback(caller, self)
    NotificationUtils.showNotificationDialog(self._commandManager, self._notification)
end

---------------------------------------------------------------------------------
function NotificationIcon:new(commandManager, notification, gameObject)
    self._commandManager = commandManager
    self._notification = notification
    self._gameObject = gameObject   -- Needed by NotificationsPanel, do not delete

    local notificationInteractionHandler = gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(NotificationIcon.showNotificationDialogCallback, self)
    
    local spriteRenderer = gameObject:findComponent("SpriteRenderer")
    spriteRenderer:setTexture(notification:getIcon())
end

return NotificationIcon