---------------------------------------------------------------------------------
local MoneyPanel = 
{
    MONEY_ICON = "MoneyIcon",
    MONEY_TEXT_NAME = "MoneyText"
}

---------------------------------------------------------------------------------
local function updateMoneyText(money, moneyText)
    moneyText:setText(tostring(money))
end

---------------------------------------------------------------------------------
function MoneyPanel:new(moneyPanelGameObject, moneyManager)
    self._moneyText = moneyPanelGameObject:findChildGameObject(self.MONEY_TEXT_NAME):findComponent("TextRenderer")
    moneyManager:subscribeOnMoneyChangedCallback(updateMoneyText, self._moneyText)
end

return MoneyPanel