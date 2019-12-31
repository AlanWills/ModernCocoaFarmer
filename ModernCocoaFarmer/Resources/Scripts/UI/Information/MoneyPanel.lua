---------------------------------------------------------------------------------
local MoneyPanel = 
{
    MONEY_TEXT_NAME = "MoneyText"
}

---------------------------------------------------------------------------------
local function updateMoneyText(eventArgs, money, moneyText)
    moneyText:setText(tostring(money))
end

---------------------------------------------------------------------------------
function MoneyPanel:new(moneyPanelGameObject, moneyManager)
    local moneyText = moneyPanelGameObject:findChildGameObject(self.MONEY_TEXT_NAME)

    self._moneyText = moneyText:findComponent("TextRenderer")
    moneyManager:subscribeOnMoneyChangedCallback(updateMoneyText, self._moneyText)
end

return MoneyPanel