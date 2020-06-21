local ShowModalDialog = require 'Commands.UI.ShowModalDialog'
local NotificationDialog = require 'UI.Notifications.NotificationDialog'
local Class = require 'OOP.Class'

local ShowNotificationDialog = Class.inheritsFrom(ShowModalDialog)

---------------------------------------------------------------------------------
function ShowNotificationDialog:new(...)
    ShowModalDialog.new(self, NotificationDialog, ...)
end

---------------------------------------------------------------------------------
function ShowNotificationDialog:execute(commandManager)
    log("Launching Notification Dialog")
    ShowModalDialog.execute(self, commandManager)
end

---------------------------------------------------------------------------------
function ShowNotificationDialog.parseArgs(args)
    local argCount = #args
    
    if argCount < 1 then
        return nil, "Missing notification title argument"
    end

    if argCount < 2 then
        return nil, "Missing notification description argument"
    end

    return args
end

return ShowNotificationDialog