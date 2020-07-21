local ShowNotificationDialog = require 'Commands.UI.Notifications.ShowNotificationDialog'

local NotificationUtils = {}

---------------------------------------------------------------------------------
function NotificationUtils.showNotificationDialog(commandManager, notification)
    local sfxPath = notification:getSfxPath()

    if sfxPath == "" then
        sfxPath = nil
    end

    commandManager:execute(
        ShowNotificationDialog, 
        notification:getName(), 
        notification:getDescription(),
        sfxPath)
end

return NotificationUtils