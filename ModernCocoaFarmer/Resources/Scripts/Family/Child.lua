local Class = require 'OOP.Class'
local Event = require 'Events.Event'

local Child = {}

---------------------------------------------------------------------------------
function Child:new(childInformation)
    self.childInformation = childInformation
    self.name = childInformation:getName()
    self._selected = false
    self._onSelectedChanged = Class.new(Event)
end

---------------------------------------------------------------------------------
local function invokeSelectedChanged(self)
    self._onSelectedChanged:invoke(self, self._selected)
end

---------------------------------------------------------------------------------
function Child:select()
    self._selected = true
    invokeSelectedChanged(self)
end

---------------------------------------------------------------------------------
function Child:deselect()
    self._selected = false
    invokeSelectedChanged(self)
end

---------------------------------------------------------------------------------
function Child:isSelected()
    return self._selected
end

---------------------------------------------------------------------------------
function Child:subscribeOnSelectedChangedCallback(key, callback, extraArgs)
    self._onSelectedChanged:subscribe(key, callback, extraArgs)
end

return Child