local InteractableBuildingDialog = 
{
    DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "InteractableBuildingDialog.prefab"),
    TITLE_TEXT_NAME = "TitleText",
    DESCRIPTION_TEXT_NAME = "DescriptionText",
    COST_ICON_NAME = "CostIcon",
    COST_TEXT_NAME = "CostText",
    CLOSE_BUTTON_NAME = "CloseButton",
    STATS_BACKGROUND_NAME = "StatsBackground",
    HEALTH_MODIFIER_TEXT_NAME = "HealthModifierText",
    SAFETY_MODIFIER_TEXT_NAME = "SafetyModifierText",
    EDUCATION_MODIFIER_TEXT_NAME = "EducationModifierText",
    HAPPINESS_MODIFIER_TEXT_NAME = "HappinessModifierText",
    SEND_CHILD_BACKGROUND_NAME = "SendChildBackground",
    SEND_CHILD_HELP_TEXT_NAME = "SendChildHelpText",
    SEND_CHILD_BUTTON_NAME = "SendChildButton",
    SEND_CHILD_BUTTON_TEXT_NAME = "SendChildButtonText",
}

----------------------------------------------------------------------------------------
local function closeCallback(eventArgs, caller)
    caller:getParent():die()
end

----------------------------------------------------------------------------------------
local function createModifierText(modifier)
    local modifierText = "";

    if modifier:isDeltaChange() then
        modifierText = modifierText .. "+"
    else
        modifierText = modifierText .. "set to "
    end

    modifierText = modifierText .. modifier:getAmount()
    modifierText = modifierText .. "%"

    if modifier:isPeriodicChange() then
        modifierText = modifierText .. " every "
        modifierText = modifierText .. modifier:getPeriodInMonths()
    end

    if modifier:getAppliesToAllChildren() then
        modifierText = modifierText .. " for all children"
    end

    return modifierText
end

----------------------------------------------------------------------------------------
local function setModifierText(statsBackground, textName, modifier)
    local text = statsBackground:findChildGameObject(textName):findComponent("TextRenderer")
    text:setText(createModifierText(modifier))
end

----------------------------------------------------------------------------------------
local function sendChildToBuilding(eventArgs, caller, self)
    self._building:sendChild(self._selectedChild)
    self._gameObject:die()
end

----------------------------------------------------------------------------------------
function InteractableBuildingDialog:new(screen, building, selectedChild)
    self._building = building
    self._selectedChild = selectedChild

    local dialogPrefab = Resources.loadPrefab(self.DIALOG_PREFAB_PATH)
    self._gameObject = dialogPrefab:instantiate(screen)
    local interactableBuildingBackground = self._gameObject:findChildGameObject("InteractableBuildingBackground")

    local titleText = interactableBuildingBackground:findChildGameObject(self.TITLE_TEXT_NAME)
    titleText:findComponent("TextRenderer"):setText(building:getName())

    local descriptionText = interactableBuildingBackground:findChildGameObject(self.DESCRIPTION_TEXT_NAME)
    descriptionText:findComponent("TextRenderer"):setText(building:getDescription())
    
    local costIcon = interactableBuildingBackground:findChildGameObject(self.COST_ICON_NAME)
    local costText = costIcon:findChildGameObject(self.COST_TEXT_NAME):findComponent("TextRenderer")
    costText:setText(tostring(building:getMoneyModifier():getAmount()))

    local closeButton = interactableBuildingBackground:findChildGameObject(self.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonUpCallback(closeCallback)

    local statsBackground = interactableBuildingBackground:findChildGameObject(self.STATS_BACKGROUND_NAME)
    setModifierText(statsBackground, self.HEALTH_MODIFIER_TEXT_NAME, building:getHealthModifier())
    setModifierText(statsBackground, self.SAFETY_MODIFIER_TEXT_NAME, building:getSafetyModifier())
    setModifierText(statsBackground, self.EDUCATION_MODIFIER_TEXT_NAME, building:getEducationModifier())
    setModifierText(statsBackground, self.HAPPINESS_MODIFIER_TEXT_NAME, building:getHappinessModifier())

    self:setUpChildSelectionUI(interactableBuildingBackground, selectedChild)
end

----------------------------------------------------------------------------------------
function InteractableBuildingDialog:setUpChildSelectionUI(parentGameObject, selectedChild)
    local sendChildBackground = parentGameObject:findChildGameObject(self.SEND_CHILD_BACKGROUND_NAME)
    local sendChildHelpText = sendChildBackground:findChildGameObject(self.SEND_CHILD_HELP_TEXT_NAME)
    local sendChildButton = sendChildBackground:findChildGameObject(self.SEND_CHILD_BUTTON_NAME)
    local isChildSelected = selectedChild ~= nil
    local isChildAlreadyAtBuilding = isChildSelected and selectedChild:isAtBuilding()
    local isChildAbleToBeSent = isChildSelected and not isChildAlreadyAtBuilding

    sendChildHelpText:setShouldRender(not isChildAbleToBeSent)
    sendChildHelpText:setActive(not isChildAbleToBeSent)
    sendChildButton:setShouldRender(isChildAbleToBeSent)
    sendChildButton:setActive(isChildAbleToBeSent)
    
    if isChildAbleToBeSent then
        local sendChildButtonInteractionHandler = sendChildButton:findComponent("MouseInteractionHandler")
        sendChildButtonInteractionHandler:subscribeOnLeftButtonUpCallback(sendChildToBuilding, self)

        local sendChildButtonText = sendChildButton:findChildGameObject(self.SEND_CHILD_BUTTON_TEXT_NAME)
        sendChildButtonText:findComponent("TextRenderer"):setText("Send " .. selectedChild:getName())
    elseif isChildAlreadyAtBuilding then
        sendChildHelpText:findComponent("TextRenderer"):setText(selectedChild:getName() .. " is already at\nthe " .. selectedChild:getCurrentBuilding())
    else
        sendChildHelpText:findComponent("TextRenderer"):setText("Select a Child to send\nthem to this building")
    end
end

return InteractableBuildingDialog