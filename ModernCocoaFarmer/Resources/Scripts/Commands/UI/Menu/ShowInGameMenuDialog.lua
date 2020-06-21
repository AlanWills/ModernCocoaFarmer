local ShowModalDialog = require 'Commands.UI.ShowModalDialog'
local InGameMenuDialog = require 'UI.Menu.InGameMenuDialog'
local Class = require 'OOP.Class'

local ShowInGameMenuDialog = Class.inheritsFrom(ShowModalDialog)

---------------------------------------------------------------------------------
function ShowInGameMenuDialog:new(...)
    ShowModalDialog.new(self, InGameMenuDialog, ...)
end

---------------------------------------------------------------------------------
function ShowInGameMenuDialog:execute(commandManager)
    log("Launching In Game Menu Dialog")
    ShowModalDialog.execute(self, commandManager)
end

return ShowInGameMenuDialog