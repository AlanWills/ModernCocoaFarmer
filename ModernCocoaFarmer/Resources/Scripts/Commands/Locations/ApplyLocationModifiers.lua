local ApplyLocationModifiers = {}

---------------------------------------------------------------------------------
function ApplyLocationModifiers:execute(commandManager)
    log("Applying location modifiers")

    local locationsManager = commandManager.locationsManager
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            local location = locationsManager:findLocation(child:getCurrentLocation())
            location:applyModifiers(child)
            
            log(location:getName() .. " modifiers applied to " ..  child:getName())
        end
    end
end

return ApplyLocationModifiers