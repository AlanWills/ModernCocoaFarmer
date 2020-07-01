local SendNotification = {}

---------------------------------------------------------------------------------
function SendNotification:new(name, description, icon, sfx)
    self._name = name
    self._description = description
    self._icon = icon
    self._sfx = sfx
end

---------------------------------------------------------------------------------
function SendNotification:execute(commandManager)
    local notification = Notification.create(self._name)
    notification:setDescription(self._description)
    notification:setIcon(self._icon)

    if self._sfx ~= nil then
        notification:setSfxPath(self._sfx)
    end

    log("Sending notification: " .. self._name)
    commandManager.notificationManager:sendNotification(notification)
end

---------------------------------------------------------------------------------
function SendNotification.parseArgs(args)
    local argCount = #args

    if argCount < 1 then
        return nil, "Missing name argument"
    end

    if argCount < 2 then
        return nil, "Missing description argument"
    end
    
    if argCount < 3 then
        return nil, "Missing icon argument"
    end

    return args
end

return SendNotification