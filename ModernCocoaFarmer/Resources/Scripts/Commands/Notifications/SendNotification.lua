local SendNotification = {}

---------------------------------------------------------------------------------
function SendNotification:new(name, description, icon)
    self._name = name
    self._description = description
    self._icon = icon
end

---------------------------------------------------------------------------------
function SendNotification:execute(commandManager)
    local notification = Notification.create(self._name)
    notification:setDescription(self._description)
    notification:setIcon(self._icon)

    commandManager.notificationManager:sendNotification(notification)
end

return SendNotification