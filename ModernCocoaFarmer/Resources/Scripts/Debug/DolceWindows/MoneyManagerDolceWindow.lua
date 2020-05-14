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
    local moneyChanged, newMoney = ImGui.inputInt("Money", self._moneyManager:getMoney())
    if moneyChanged then
        self._moneyManager:setMoney(newMoney)
    end

    local salaryLevelChanged, newSalaryLevel = ImGui.inputUInt("Salary Level", self._moneyManager:getSalaryLevel())
    if salaryLevelChanged then
        self._moneyManager:setSalaryLevel(newSalaryLevel)
    end
end

return MoneyManagerDolceWindow