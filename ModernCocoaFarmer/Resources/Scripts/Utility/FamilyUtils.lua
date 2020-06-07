local FamilyUtils = {}

---------------------------------------------------------------------------------
function FamilyUtils.getActivatedChildCount(familyManager)
    local count = 0

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        if familyManager:getChild(childIndex):isActivated() then
            count = count + 1
        end
    end

    return count
end

---------------------------------------------------------------------------------
function FamilyUtils.getFirstNotBornChild(familyManager)
    for childIndex = familyManager:getChildCount() - 1, 1, -1 do
        local child = familyManager:getChild(childIndex)
        if child:isNotBorn() then
            return child
        end
    end

    return nil
end

return FamilyUtils