local csd = {}

----------------------------------------------------------------------------------------
csd.DIALOG_PREFAB_PATH = "Prefabs\\UI\\Family\\ChildStatsDialog.prefab"
csd.DIALOG_PREFAB = nil
csd.HEALTH_PROGRESS_BAR_NAME = "HealthProgressBar"
csd.SAFETY_PROGRESS_BAR_NAME = "SafetyProgressBar"
csd.EDUCATION_PROGRESS_BAR_NAME = "EducationProgressBar"
csd.HAPPINESS_PROGRESS_BAR_NAME = "HappinessProgressBar"

----------------------------------------------------------------------------------------
function csd.load()
    csd.DIALOG_PREFAB = Resources.loadPrefab(csd.DIALOG_PREFAB_PATH)
    return csd.DIALOG_PREFAB
end

----------------------------------------------------------------------------------------
function csd.unload()
    Resources.unloadPrefab(csd.DIALOG_PREFAB)
    csd.DIALOG_PREFAB = nil
end

----------------------------------------------------------------------------------------
local function setUpProgressBar(dialogGameObject, categoryName, progressBarName, value)
    local category = dialogGameObject:findChildGameObject(categoryName)
    local categoryBackground = category:findChildGameObject(categoryName .. "ProgressBarBackground")
    local categoryProgressBarGameObject = categoryBackground:findChildGameObject(progressBarName)
    local categoryProgressBar = categoryProgressBarGameObject:findComponent("ProgressBar")
    categoryProgressBar:setProgress(value)
end

----------------------------------------------------------------------------------------
function csd.show(screen, childInformation)
    assert(csd.DIALOG_PREFAB ~= nil)
    local dialogGameObject = csd.DIALOG_PREFAB:instantiate(screen)

    -- Health
    setUpProgressBar(dialogGameObject, "Health", csd.HEALTH_PROGRESS_BAR_NAME, childInformation:getHealth())
    
    -- Safety
    setUpProgressBar(dialogGameObject, "Safety", csd.SAFETY_PROGRESS_BAR_NAME, childInformation:getSafety())

    -- Education
    setUpProgressBar(dialogGameObject, "Education", csd.EDUCATION_PROGRESS_BAR_NAME, childInformation:getEducation())

    -- Happiness
    setUpProgressBar(dialogGameObject, "Happiness", csd.HAPPINESS_PROGRESS_BAR_NAME, childInformation:getHappiness())

    return dialogGameObject;
end

return csd