local PayBills = 
{
    information = GameEvent.load(path.combine("Data", "Events", "PayBills.asset")),
}

---------------------------------------------------------------------------------
function PayBills:new()
    self._hasEnoughMoney = true
end

---------------------------------------------------------------------------------
function PayBills:getName()
    return self.information:getName()
end

---------------------------------------------------------------------------------
function PayBills:getDescription()
    if self._hasEnoughMoney then
        return self.information:getDescription()
    end

    return "Not enough money"
end

---------------------------------------------------------------------------------
function PayBills:execute(state)
    -- Average house size is 32 m2
    -- $700 a year for 32 m2 apartment
    -- $52 a year for food per person

    self._hasEnoughMoney = state.moneyManager:getMoney() >= 430500 + 31980 * state.familyManager:getChildCount()
    
    if not self._hasEnoughMoney then
        -- Apply detrimental modifiers to children
        local childCount = 0
        while childCount < state.familyManager:getChildCount() do
            state.familyManager:getChild(childCount):setHealth(50)
            childCount = childCount + 1
        end
    end
end

return PayBills