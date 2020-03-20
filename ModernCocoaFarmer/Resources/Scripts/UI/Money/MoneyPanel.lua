---------------------------------------------------------------------------------
local MoneyPanel = 
{
    MONEY_TEXT_NAME = "MoneyText"
}

---------------------------------------------------------------------------------
function MoneyPanel:new(dataStore, moneyPanelGameObject)
    self._dataStore = dataStore
    self._moneyText = moneyPanelGameObject:findChild(self.MONEY_TEXT_NAME):findComponent("TextRenderer")
end

---------------------------------------------------------------------------------
function MoneyPanel:updateUI()
    self:setMoneyText(self._dataStore:getInt(MoneyDataSources.CURRENT_MONEY))
end

---------------------------------------------------------------------------------
function MoneyPanel:setMoneyText(money)
    self._moneyText:setText(tostring(money))
end

return MoneyPanel