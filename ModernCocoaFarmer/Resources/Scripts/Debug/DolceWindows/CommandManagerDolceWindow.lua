local CommandParsing = require 'Parsing.CommandParsing'
local Class = require 'OOP.Class'

local CommandManagerDolceWindow = 
{
    NAME = "Command Manager"
}

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:new(commandManager)
    self._commandManager = commandManager
    self._commands = {}
    self._commandText = ""
    self._output = ""

    self:addCommands()
end

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:addCommands()
    self._commands["AddChild"] = require 'Commands.Family.AddChild'
    self._commands["ApplyFamilyModifiers"] = require 'Commands.Family.ApplyFamilyModifiers'
    self._commands["DeselectChild"] = require 'Commands.Family.DeselectChild'
    self._commands["SelectChild"] = require 'Commands.Family.SelectChild'
    self._commands["ToggleChildSelection"] = require 'Commands.Family.ToggleChildSelection'
    self._commands["UpdateChildrenStates"] = require 'Commands.Family.ToggleChildSelection'
    self._commands["UpdateChildrenTimes"] = require 'Commands.Family.UpdateChildrenTimes'
    self._commands["ActivateLocation"] = require 'Commands.Locations.ActivateLocation'
    self._commands["ApplyLocationModifiers"] = require 'Commands.Locations.ApplyLocationModifiers'
    self._commands["LeaveChild"] = require 'Commands.Locations.LeaveChild'
    self._commands["SendChildToLocation"] = require 'Commands.Locations.SendChildToLocation'
    self._commands["AddMoney"] = require 'Commands.Money.AddMoney'
    self._commands["DecreaseSalaryLevel"] = require 'Commands.Money.DecreaseSalaryLevel'
    self._commands["IncreaseSalaryLevel"] = require 'Commands.Money.IncreaseSalaryLevel'
    self._commands["SendNotification"] = require 'Commands.Notifications.SendNotification'
    self._commands["Finish"] = require 'Commands.State.Finish'
    self._commands["Load"] = require 'Commands.State.Load'
    self._commands["Save"] = require 'Commands.State.Save'
    self._commands["ElapseTime"] = require 'Commands.Time.ElapseTime'
    self._commands["Pause"] = require 'Commands.Time.Pause'
    self._commands["Play"] = require 'Commands.Time.Play'
    self._commands["ShowLocationDialog"] = require 'Commands.UI.Locations.ShowLocationDialog'
    self._commands["ShowInGameMenuDialog"] = require 'Commands.UI.Menu.ShowInGameMenuDialog'
    self._commands["ShowNotificationDialog"] = require 'Commands.UI.Notifications.ShowNotificationDialog'
end

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:findCommand(commandName)
    if self._commands[commandName] ~= nil then
        return self._commands[commandName]
    end

    for name, command in pairs(self._commands) do
        if name:find(commandName) ~= nil then
            return command
        end
    end
end

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:render()
    self._commandText = ImGui.inputText("Command", self._commandText)

    if ImGui.button("Execute") then
        local tokens = CommandParsing.parse(self._commandText)

        if #tokens < 1 then
            self._output = "Invalid Input: no command detected"
        else
            local commandName = table.remove(tokens, 1)
            local command = self:findCommand(commandName)

            if command == nil then
                self._output = "Invalid Input: unknown command " .. commandName
            else
                if command.parseArgs ~= nil then
                    local args, error = command.parseArgs(tokens)

                    if args ~= nil then
                        self._output = ""
                        Class.new(command, table.unpack(args)):execute(self._commandManager)
                    else
                        self._output = "Failed To Create Args: " .. error
                    end
                else
                    self._output = ""
                    Class.new(command):execute(self._commandManager)
                end
            end
        end
    end

    ImGui.text(self._output)
end

return CommandManagerDolceWindow