---------------------------------------------------------------------------------
local MoneyPanel = 
{
    MONEY_TEXT_NAME = "MoneyText"
}

---------------------------------------------------------------------------------
function MoneyPanel:new(moneyManager, moneyPanelGameObject)
    self._moneyManager = moneyManager
    self._moneyText = moneyPanelGameObject:findChildGameObject(self.MONEY_TEXT_NAME):findComponent("TextRenderer")
end

---------------------------------------------------------------------------------
function MoneyPanel:updateUI()
    self:setMoneyText(self._moneyManager:getMoney())
end

---------------------------------------------------------------------------------
function MoneyPanel:setMoneyText(money)
    self._moneyText:setText(tostring(money))
end

return MoneyPanel