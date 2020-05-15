local FamilyManagerDolceWindow = 
{
    NAME = "Family Manager"
}

---------------------------------------------------------------------------------
function FamilyManagerDolceWindow:new(familyManager)
    self._familyManager = familyManager
end

---------------------------------------------------------------------------------
function FamilyManagerDolceWindow:render()
    if self._familyManager:canAddChild() and ImGui.button("Add Child") then
        self._familyManager:addChild()
    end

    for childIndex = 0, (self._familyManager:getChildCount() - 1) do
        self:renderChild(self._familyManager:getChild(childIndex))
    end
end

---------------------------------------------------------------------------------
function FamilyManagerDolceWindow:renderChild(child)
    if ImGui.treeNode(child:getName()) then
        child:setHealth(ImGui.inputFloat("Health", child:getHealth()))
        child:setSafety(ImGui.inputFloat("Safety", child:getSafety()))
        child:setEducation(ImGui.inputFloat("Education", child:getEducation()))
        child:setHappiness(ImGui.inputFloat("Happiness", child:getHappiness()))

        ImGui.text("CurrentLocation: " .. child:getCurrentLocation())
        child:setTimeAtLocation(ImGui.inputFloat("Time At Location", child:getTimeAtLocation()))

        ImGui.treePop()
    end
end

return FamilyManagerDolceWindow