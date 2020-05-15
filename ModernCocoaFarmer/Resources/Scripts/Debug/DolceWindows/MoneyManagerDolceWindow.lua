local MoneyManagerDolceWindow = 
{
    NAME = "Money Manager"
}

---------------------------------------------------------------------------------
function MoneyManagerDolceWindow:new(moneyManager)
    self._moneyManager = moneyManager
end

---------------------------------------------------------------------------------
function MoneyManagerDolceWindow:render()
    self._moneyManager:setMoney(ImGui.inputInt("Money", self._moneyManager:getMoney()))
    self._moneyManager:setSalaryLevel(ImGui.inputUInt("Salary Level", self._moneyManager:getSalaryLevel()))
end

return MoneyManagerDolceWindow