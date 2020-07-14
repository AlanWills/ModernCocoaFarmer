local Class = require 'OOP.Class'
local NotificationIcon = require 'UI.Notifications.NotificationIcon'

local NotificationsPanel = 
{
    NOTIFICATION_ICON_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationIcon.prefab"),
    NOTIFICATIONS_ANCHOR_NAME = "NotificationsAnchor",
    REMOVE_ALL_NOTIFICATIONS_BUTTON_NAME = "RemoveAllNotificationsButton",
    MAX_NUM_NOTIFICATIONS = 9,
}

---------------------------------------------------------------------------------
function NotificationsPanel.createNotificationIconCallback(notification, self)
    self:createNotificationIcon(notification) 
end

---------------------------------------------------------------------------------
function NotificationsPanel.removeNotificationCallback(caller, extraArgs)
    extraArgs.self:removeNotificationViaIcon(extraArgs.notificationIcon)
end

---------------------------------------------------------------------------------
function NotificationsPanel.removeAllNotificationsCallback(caller, self)
    self:removeAllNotifications()
end

---------------------------------------------------------------------------------
function NotificationsPanel:new(commandManager, notificationsPanelGameObject)
    self._commandManager = commandManager
    self._gameObject = notificationsPanelGameObject
    self._notificationsAnchor = notificationsPanelGameObject:findChild(self.NOTIFICATIONS_ANCHOR_NAME)

    local notificationManager = commandManager.notificationManager
    local notificationCount = 0

    while notificationCount < notificationManager:getNotificationCount() do
        self:createNotificationIcon(notificationManager:getNotification(notificationCount))
        notificationCount = notificationCount + 1
    end

    notificationManager:subscribeOnNotificationSentCallback(NotificationsPanel.createNotificationIconCallback, self)

    self._gameObject:setupChildLeftButtonUpCallback(self.REMOVE_ALL_NOTIFICATIONS_BUTTON_NAME, NotificationsPanel.removeAllNotificationsCallback, self)
end

---------------------------------------------------------------------------------
function NotificationsPanel:createNotificationIcon(notification)
    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    local notificationGameObject = notificationPrefab:instantiate()
    local notificationIcon = Class.new(NotificationIcon, self._commandManager, notification, notificationGameObject)

    local notificationInteractionHandler = notificationGameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(NotificationsPanel.removeNotificationCallback, { self = self, notificationIcon = notificationIcon })
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(NotificationsPanel.removeNotificationCallback, { self = self, notificationIcon = notificationIcon })

    self._notificationsAnchor:findComponent("StackPanel"):addChild(notificationGameObject)

    self:removeOldNotifications()
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeNotificationViaIcon(notificationIcon)
    self._commandManager.notificationManager:removeNotification(notificationIcon._notification)
    self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationIcon._gameObject)
    notificationIcon._gameObject:destroy()
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeNotificationViaIndex(notificationIndex)
    local notificationGameObject = self._notificationsAnchor:getChild(notificationIndex)

    self._commandManager.notificationManager:removeNotification(notificationIndex)
    self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationGameObject)
    notificationGameObject:destroy()
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeOldNotifications()
    local numNotificationIcons = self._notificationsAnchor:getChildCount()
    
    for i = (numNotificationIcons - NotificationsPanel.MAX_NUM_NOTIFICATIONS - 1), 0, -1 do
        self:removeNotificationViaIndex(i)
    end
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeAllNotifications()
    local numNotificationIcons = self._notificationsAnchor:getChildCount()
    
    for i = numNotificationIcons - 1, 0, -1 do
        self:removeNotificationViaIndex(i)
    end
end

return NotificationsPanel