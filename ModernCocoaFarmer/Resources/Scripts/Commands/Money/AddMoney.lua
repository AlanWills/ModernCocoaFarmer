local AddMoney = {}

---------------------------------------------------------------------------------
function AddMoney:new(amount)
    self._amount = amount
end

---------------------------------------------------------------------------------
function AddMoney:execute(commandManager)
    log("Adding money " .. tostring(self._amount))

    local modifier = Modifier.create("Money Modifier")
    modifier:setAmount(self._amount)
    modifier:setChangeType("Delta")

    commandManager.moneyManager:applyMoneyModifier(modifier)
end

return AddMoney