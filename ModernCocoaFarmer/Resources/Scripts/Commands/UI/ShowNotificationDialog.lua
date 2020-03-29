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
    ShowModalDialog.execute(self, commandManager)
end

return ShowNotificationDialog