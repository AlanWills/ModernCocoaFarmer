local ChildStatsDialog = 
{
    DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Family", "ChildStatsDialog.prefab"),
    HEALTH_PROGRESS_BAR_NAME = "HealthProgressBar",
    SAFETY_PROGRESS_BAR_NAME = "SafetyProgressBar",
    EDUCATION_PROGRESS_BAR_NAME = "EducationProgressBar",
    HAPPINESS_PROGRESS_BAR_NAME = "HappinessProgressBar",
    CURRENT_BUILDING_NAME = "CurrentBuilding",
    CURRENT_BUILDING_TEXT_NAME = "CurrentBuildingText",
}

----------------------------------------------------------------------------------------
local function getProgressBar(dialogGameObject, categoryName, progressBarName)
    local category = dialogGameObject:findChildGameObject(categoryName)
    local categoryBackground = category:findChildGameObject(categoryName .. "ProgressBarBackground")
    local categoryProgressBarGameObject = categoryBackground:findChildGameObject(progressBarName)
    
    return categoryProgressBarGameObject:findComponent("ProgressBar")
end

----------------------------------------------------------------------------------------
function ChildStatsDialog:new(parent, child)
    self._child = child

    local prefab = Resources.loadPrefab(self.DIALOG_PREFAB_PATH)
    local gameObject = prefab:instantiate(parent:getScreen())
    gameObject:setParent(parent);
    gameObject:getTransform():translate(0, -240)
    self._gameObject = gameObject

    self._healthProgessBar = getProgressBar(gameObject, "Health", self.HEALTH_PROGRESS_BAR_NAME)
    self._safetyProgressBar = getProgressBar(gameObject, "Safety", self.SAFETY_PROGRESS_BAR_NAME)
    self._educationProgressBar = getProgressBar(gameObject, "Education", self.EDUCATION_PROGRESS_BAR_NAME)
    self._happinessProgressBar = getProgressBar(gameObject, "Happiness", self.HAPPINESS_PROGRESS_BAR_NAME)

    local childBuildingGameObject = gameObject:findChildGameObject(self.CURRENT_BUILDING_NAME)
    self._childBuildingText = childBuildingGameObject:findChildGameObject(self.CURRENT_BUILDING_TEXT_NAME):findComponent("TextRenderer")
end

----------------------------------------------------------------------------------------
function ChildStatsDialog:show()
    self._gameObject:setActive(true)
    self._gameObject:setShouldRender(true)
end

----------------------------------------------------------------------------------------
function ChildStatsDialog:hide()
    self._gameObject:setActive(false)
    self._gameObject:setShouldRender(false)
end

----------------------------------------------------------------------------------------
function ChildStatsDialog:isShowing()
    return self._gameObject:isActive() and self._gameObject:shouldRender()
end

----------------------------------------------------------------------------------------
function ChildStatsDialog:updateUI()
    self._healthProgessBar:setProgress(self._child:getHealth())
    self._safetyProgressBar:setProgress(self._child:getSafety())
    self._educationProgressBar:setProgress(self._child:getEducation())
    self._happinessProgressBar:setProgress(self._child:getHappiness())

    local locationText = "Not at location"
    if self._child:isAtBuilding() then
        locationText = "Currently at " .. self._child:getCurrentBuilding()
    end

    self._childBuildingText:setText(locationText)
end

return ChildStatsDialog