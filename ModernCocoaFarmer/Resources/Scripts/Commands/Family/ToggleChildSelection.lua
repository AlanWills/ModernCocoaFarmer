local ToggleChildSelection = {}

---------------------------------------------------------------------------------
function ToggleChildSelection:new(child)
    self._child = child
end

---------------------------------------------------------------------------------
function ToggleChildSelection:execute(commandManager)
    local hasSelectedChild = commandManager.familyManager:hasSelectedChild()
    local isChildSelectedChild = hasSelectedChild and commandManager.familyManager:getSelectedChild() == self._child

    if isChildSelectedChild then
        log("Deselecting child " .. self._child:getName())
        commandManager.familyManager:deselectOnlyThisChild(self._child)
    else
        log("Selecting child " .. self._child:getName())
        commandManager.familyManager:selectOnlyThisChild(self._child)
    end
end

return ToggleChildSelection