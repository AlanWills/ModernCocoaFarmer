local ibd = {}

----------------------------------------------------------------------------------------
ibd.DIALOG_PREFAB_PATH = "Prefabs\\UI\\InteractableBuildingDialog.prefab"
ibd.TITLE_TEXT_NAME = "TitleText"
ibd.DESCRIPTION_TEXT_NAME = "DescriptionText"
ibd.CLOSE_BUTTON_NAME = "CloseButton"
ibd.STATS_BACKGROUND_NAME = "StatsBackground"
ibd.HEALTH_MODIFIER_TEXT_NAME = "HealthModifierText"
ibd.SAFETY_MODIFIER_TEXT_NAME = "SafetyModifierText"
ibd.EDUCATION_MODIFIER_TEXT_NAME = "EducationModifierText"
ibd.HAPPINESS_MODIFIER_TEXT_NAME = "HappinessModifierText"

----------------------------------------------------------------------------------------
local function closeCallback(eventArgs, caller)
    caller:getParent():setShouldRender(false)

    local limitedLifeTime = caller:addComponent("LimitedLifeTime")
    limitedLifeTime:setLifeTime(0)
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
function ibd.load()
    return Resources.loadPrefab(ibd.DIALOG_PREFAB_PATH)
end

----------------------------------------------------------------------------------------
function ibd.show(screen, buildingInformation)
    local dialogPrefab = ibd.load()
    local dialogGameObject = dialogPrefab:instantiate(screen)

    local titleText = dialogGameObject:findChildGameObject(ibd.TITLE_TEXT_NAME)
    titleText:findComponent("TextRenderer"):setText(buildingInformation:getName())

    local descriptionText = dialogGameObject:findChildGameObject(ibd.DESCRIPTION_TEXT_NAME)
    descriptionText:findComponent("TextRenderer"):setText(buildingInformation:getDescription())

    local closeButton = dialogGameObject:findChildGameObject(ibd.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonClickedCallback(closeCallback)

    local statsBackground = dialogGameObject:findChildGameObject(ibd.STATS_BACKGROUND_NAME)
    setModifierText(statsBackground, ibd.HEALTH_MODIFIER_TEXT_NAME, buildingInformation:getHealthModifier())
    setModifierText(statsBackground, ibd.SAFETY_MODIFIER_TEXT_NAME, buildingInformation:getSafetyModifier())
    setModifierText(statsBackground, ibd.EDUCATION_MODIFIER_TEXT_NAME, buildingInformation:getEducationModifier())
    setModifierText(statsBackground, ibd.HAPPINESS_MODIFIER_TEXT_NAME, buildingInformation:getHappinessModifier())
end

return ibd