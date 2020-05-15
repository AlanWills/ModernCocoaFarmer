local CommandManagerDolceWindow = 
{
    NAME = "Command Manager"
}

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:new(commandManager)
    self._commandManager = commandManager
end

---------------------------------------------------------------------------------
function CommandManagerDolceWindow:render()
    if ImGui.button("Test") then
        local string = 'Commands.Money.AddMoney'
        local Command = require(string)

        self._commandManager:execute(Command, 123)
    end
end

return CommandManagerDolceWindow