local Class = require 'OOP.Class'
local ShowNotificationDialog = require 'Commands.UI.Notifications.ShowNotificationDialog'

local NotificationIcon = {}

---------------------------------------------------------------------------------
local function showNotificationDialogCallback(caller, self)
    self._commandManager:execute(ShowNotificationDialog, self._title, self._description)
end

---------------------------------------------------------------------------------
function NotificationIcon:new(commandManager, notification, gameObject)
    self._commandManager = commandManager
    self._title = notification:getName()
    self._description = notification:getDescription()
    self._gameObject = gameObject   -- Needed by NotificationsPanel, do not delete

    local notificationInteractionHandler = gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(showNotificationDialogCallback, self)
    
    local spriteRenderer = gameObject:findComponent("SpriteRenderer")
    spriteRenderer:setTexture(notification:getIcon())
end

return NotificationIcon