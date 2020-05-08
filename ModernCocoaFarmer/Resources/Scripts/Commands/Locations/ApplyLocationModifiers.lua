local ApplyLocationModifiers = {}

---------------------------------------------------------------------------------
function ApplyLocationModifiers:execute(commandManager)
    local locationsManager = commandManager.locationsManager
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            local location = locationsManager:findLocation(child:getCurrentLocation())
            location:applyModifiers(child)
        end
    end
end

return ApplyLocationModifiers