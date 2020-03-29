local ChildStatsPanel = 
{
    PANEL_PREFAB_PATH = path.combine("Prefabs", "UI", "Family", "ChildStatsPanel.prefab"),
    HEALTH_PROGRESS_BAR_NAME = "HealthProgressBar",
    SAFETY_PROGRESS_BAR_NAME = "SafetyProgressBar",
    EDUCATION_PROGRESS_BAR_NAME = "EducationProgressBar",
    HAPPINESS_PROGRESS_BAR_NAME = "HappinessProgressBar",
    CURRENT_LOCATION_NAME = "CurrentLocation",
    CURRENT_LOCATION_TEXT_NAME = "CurrentLocationText",
}

----------------------------------------------------------------------------------------
local function getProgressBar(dialogGameObject, categoryName, progressBarName)
    local category = dialogGameObject:findChild(categoryName)
    local categoryBackground = category:findChild(categoryName .. "ProgressBarBackground")
    local categoryProgressBarGameObject = categoryBackground:findChild(progressBarName)
    
    return categoryProgressBarGameObject:findComponent("ProgressBar")
end

----------------------------------------------------------------------------------------
function ChildStatsPanel:new(dataStore, childName, parent)
    self._dataStore = dataStore
    self._childName = childName

    local prefab = Resources.loadPrefab(self.PANEL_PREFAB_PATH)
    local gameObject = prefab:instantiate()
    gameObject:setParent(parent);
    gameObject:getTransform():translate(0, -240)
    self._gameObject = gameObject

    self._healthProgessBar = getProgressBar(gameObject, "Health", self.HEALTH_PROGRESS_BAR_NAME)
    self._safetyProgressBar = getProgressBar(gameObject, "Safety", self.SAFETY_PROGRESS_BAR_NAME)
    self._educationProgressBar = getProgressBar(gameObject, "Education", self.EDUCATION_PROGRESS_BAR_NAME)
    self._happinessProgressBar = getProgressBar(gameObject, "Happiness", self.HAPPINESS_PROGRESS_BAR_NAME)

    local childLocationGameObject = gameObject:findChild(self.CURRENT_LOCATION_NAME)
    self._childLocationText = childLocationGameObject:findChild(self.CURRENT_LOCATION_TEXT_NAME):findComponent("TextRenderer")
end

----------------------------------------------------------------------------------------
function ChildStatsPanel:show()
    self._gameObject:setActive(true)
end

----------------------------------------------------------------------------------------
function ChildStatsPanel:hide()
    self._gameObject:setActive(false)
end

----------------------------------------------------------------------------------------
function ChildStatsPanel:isShowing()
    return self._gameObject:isActive()
end

----------------------------------------------------------------------------------------
function ChildStatsPanel:updateUI()
    local childData = self._dataStore:getObject(FamilyDataSources.CHILDREN .. "." .. self._childName)

    self._healthProgessBar:setProgress(childData:getFloat(FamilyDataSources.HEALTH))
    self._safetyProgressBar:setProgress(childData:getFloat(FamilyDataSources.SAFETY))
    self._educationProgressBar:setProgress(childData:getFloat(FamilyDataSources.EDUCATION))
    self._happinessProgressBar:setProgress(childData:getFloat(FamilyDataSources.HAPPINESS))

    local locationText = "Not at location"
    if childData:getBool(FamilyDataSources.IS_AT_LOCATION) then
        locationText = childData:getString(FamilyDataSources.CURRENT_LOCATION)
    end

    self._childLocationText:setText(locationText)
end

return ChildStatsPanel