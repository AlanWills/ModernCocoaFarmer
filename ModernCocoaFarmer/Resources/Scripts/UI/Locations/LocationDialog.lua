local LocationDialog = 
{
    DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Locations", "LocationDialog.prefab"),
    TITLE_TEXT_NAME = "TitleText",
    DESCRIPTION_TEXT_NAME = "DescriptionText",
    COST_ICON_NAME = "CostIcon",
    COST_TEXT_NAME = "CostText",
    TIME_ICON_NAME = "TimeIcon",
    TIME_TEXT_NAME = "TimeText",
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
local function closeCallback(caller)
    caller:getParent():destroy()
end

----------------------------------------------------------------------------------------
local function formatCostString(cost)
    if cost ~= 0 then
        return string.format("%d", cost)
    else
        return "Free"
    end
end

----------------------------------------------------------------------------------------
local function formatTimeString(daysToComplete)
    local years = math.floor(daysToComplete / 360)
    local months = math.floor((daysToComplete - 360 * years) / 30)
    local days = math.floor((daysToComplete - 360 * years - 30 * months))

    local timeString = ""

    if years > 0 then
        timeString = timeString .. tostring(years) .. "y "
    end

    if months > 0 then
        timeString = timeString .. tostring(months) .. "mo "
    end

    if days > 0 then
        timeString = timeString .. tostring(days) .. "d"
    end

    return timeString
end

----------------------------------------------------------------------------------------
local function formatModifierString(modifier)
    local modifierText = "";

    if modifier:isDeltaChange() then
        modifierText = modifierText .. "+"
    else
        modifierText = modifierText .. "set to "
    end

    modifierText = modifierText .. string.format("%d", modifier:getAmount())
    modifierText = modifierText .. "%"

    if modifier:isPeriodicChange() then
        modifierText = modifierText .. " every "
        modifierText = modifierText .. string.format("%d", modifier:getPeriodInMonths())
    end

    if modifier:getAppliesToAllChildren() then
        modifierText = modifierText .. " for all children"
    end

    return modifierText
end

----------------------------------------------------------------------------------------
local function setModifierText(statsBackground, textName, modifier)
    local text = statsBackground:findChild(textName):findComponent("TextRenderer")
    text:setText(formatModifierString(modifier))
end

----------------------------------------------------------------------------------------
local function sendChildToLocation(caller, self)
    self._location:sendChild(self._selectedChild)
    self._gameObject:destroy()
end

----------------------------------------------------------------------------------------
function LocationDialog:new(location, selectedChild)
    self._location = location
    self._selectedChild = selectedChild

    local dialogPrefab = Resources.loadPrefab(self.DIALOG_PREFAB_PATH)
    self._gameObject = dialogPrefab:instantiate()
    local interactableLocationBackground = self._gameObject:findChild("InteractableLocationBackground")

    local titleText = interactableLocationBackground:findChild(self.TITLE_TEXT_NAME)
    titleText:findComponent("TextRenderer"):setText(location:getName())

    local descriptionText = interactableLocationBackground:findChild(self.DESCRIPTION_TEXT_NAME)
    descriptionText:findComponent("TextRenderer"):setText(location:getDescription())
    
    local costIcon = interactableLocationBackground:findChild(self.COST_ICON_NAME)
    local costText = costIcon:findChild(self.COST_TEXT_NAME):findComponent("TextRenderer")
    costText:setText(tostring(formatCostString(location:getMoneyModifier():getAmount())))

    local timeIcon = interactableLocationBackground:findChild(self.TIME_ICON_NAME)
    local timeText = timeIcon:findChild(self.TIME_TEXT_NAME):findComponent("TextRenderer")
    timeText:setText(formatTimeString(location:getDaysToComplete()))

    local closeButton = interactableLocationBackground:findChild(self.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonUpCallback(closeCallback)

    local statsBackground = interactableLocationBackground:findChild(self.STATS_BACKGROUND_NAME)
    setModifierText(statsBackground, self.HEALTH_MODIFIER_TEXT_NAME, location:getHealthModifier())
    setModifierText(statsBackground, self.SAFETY_MODIFIER_TEXT_NAME, location:getSafetyModifier())
    setModifierText(statsBackground, self.EDUCATION_MODIFIER_TEXT_NAME, location:getEducationModifier())
    setModifierText(statsBackground, self.HAPPINESS_MODIFIER_TEXT_NAME, location:getHappinessModifier())

    self:setUpChildSelectionUI(interactableLocationBackground, selectedChild)
end

----------------------------------------------------------------------------------------
function LocationDialog:setUpChildSelectionUI(parentGameObject, selectedChild)
    local sendChildBackground = parentGameObject:findChild(self.SEND_CHILD_BACKGROUND_NAME)
    local sendChildHelpText = sendChildBackground:findChild(self.SEND_CHILD_HELP_TEXT_NAME)
    local sendChildButton = sendChildBackground:findChild(self.SEND_CHILD_BUTTON_NAME)
    local isChildSelected = selectedChild ~= nil
    local isChildAlreadyAtLocation = isChildSelected and selectedChild:isAtLocation()
    local isChildAbleToBeSent = isChildSelected and not isChildAlreadyAtLocation

    sendChildHelpText:setShouldRender(not isChildAbleToBeSent)
    sendChildHelpText:setActive(not isChildAbleToBeSent)
    sendChildButton:setShouldRender(isChildAbleToBeSent)
    sendChildButton:setActive(isChildAbleToBeSent)
    
    if isChildAbleToBeSent then
        local sendChildButtonInteractionHandler = sendChildButton:findComponent("MouseInteractionHandler")
        sendChildButtonInteractionHandler:subscribeOnLeftButtonUpCallback(sendChildToLocation, self)

        local sendChildButtonText = sendChildButton:findChild(self.SEND_CHILD_BUTTON_TEXT_NAME)
        sendChildButtonText:findComponent("TextRenderer"):setText("Send " .. selectedChild:getName())
    elseif isChildAlreadyAtLocation then
        sendChildHelpText:findComponent("TextRenderer"):setText(selectedChild:getName() .. " is already at\nthe " .. selectedChild:getCurrentLocation())
    else
        sendChildHelpText:findComponent("TextRenderer"):setText("Select a Child to send\nthem to this location")
    end
end

return LocationDialog
