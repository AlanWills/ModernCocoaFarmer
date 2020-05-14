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
        local healthChanged, newHealth = ImGui.inputFloat("Health", child:getHealth())
        if healthChanged then
            child:setHealth(newHealth)
        end

        local safetyChanged, newSafety = ImGui.inputFloat("Safety", child:getSafety())
        if safetyChanged then
            child:setSafety(newSafety)
        end

        local educationChanged, newEducation = ImGui.inputFloat("Education", child:getEducation())
        if educationChanged then
            child:setEducation(newEducation)
        end

        local happinessChanged, newHappiness = ImGui.inputFloat("Happiness", child:getHappiness())
        if happinessChanged then
            child:setHappiness(newHappiness)
        end

        ImGui.text("CurrentLocation: " .. child:getCurrentLocation())

        local timeAtLocationChanged, newTimeAtLocation = ImGui.inputFloat("Time At Location", child:getTimeAtLocation())
        if timeAtLocationChanged and newTimeAtLocation >= 0 then
            child:setTimeAtLocation(newTimeAtLocation)
        end

        ImGui.treePop()
    end
end

return FamilyManagerDolceWindow