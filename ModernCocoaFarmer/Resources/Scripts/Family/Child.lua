local Class = require 'OOP.Class'

local Child = Class.declare()

---------------------------------------------------------------------------------
function Child.new(childInformation)
    local child = Class.new(Child)

    child.childInformation = childInformation
    child.name = childInformation:getName()
    child._selected = false
    child._onSelectedChanged = {}

    return child
end

---------------------------------------------------------------------------------
local function invokeSelectedChanged(self)
    for k, event in pairs(self._onSelectedChanged) do
        event.callback(self, self._selected, event.extraArgs)
    end
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
    local event = {}
    event.callback = callback
    event.extraArgs = extraArgs

    self._onSelectedChanged[key] = event
end

return Child