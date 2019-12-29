local Class = require 'OOP.Class'
local Event = require 'Events.Event'

local MoneyManager = 
{
    STARTING_MONEY = 100
}

---------------------------------------------------------------------------------
function MoneyManager:new()
    self._money = self.STARTING_MONEY
    self._onMoneyChanged = Class.new(Event)
end

---------------------------------------------------------------------------------
function MoneyManager:getMoney()
    return self._money
end

---------------------------------------------------------------------------------
local function invokeOnMoneyChanged(self)
    self._onMoneyChanged(self:getMoney())
end

---------------------------------------------------------------------------------
function MoneyManager:addMoney(money)
    self._money = self._money + money
    invokeOnMoneyChanged(self)
end

---------------------------------------------------------------------------------
function MoneyManager:subscribeOnMoneyChangedCallback(name, callback, extraArgs)
    self._onMoneyChanged:subscribe(name, callback, extraArgs)
end

return MoneyManager