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

---------------------------------------------------------------------------------
function AddMoney.parseArgs(args)
    if #args < 1 then
        return nil, "Missing amount argument"
    end

    log(args[1])
    args[1] = tonumber(args[1])
    return args
end

return AddMoney