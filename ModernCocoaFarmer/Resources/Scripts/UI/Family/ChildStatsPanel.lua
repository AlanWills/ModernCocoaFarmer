local csd = {}

----------------------------------------------------------------------------------------
csd.DIALOG_PREFAB_PATH
csd.DIALOG_PREFAB
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
function csd.show(screen, childInformation)
    assert(csd.DIALOG_PREFAB ~= nil)
    local dialogGameObject = csd.DIALOG_PREFAB:instantiate(screen)

    -- Health
    local healthProgressBarGameObject = dialogGameObject:findChildGameObject(csd.HEALTH_PROGRESS_BAR_NAME)
    healthProgressBarGameObject:findComponent("ProgressBar"):setValue(childInformation:getHealth())

    -- Safety
    local safetyProgressBarGameObject = dialogGameObject:findChildGameObject(csd.SAFETY_PROGRESS_BAR_NAME)
    safetyProgressBarGameObject:findComponent("ProgressBar"):setValue(childInformation:getSafety())
    
    -- Education
    local educationProgressBarGameObject = dialogGameObject:findChildGameObject(csd.EDUCATION_PROGRESS_BAR_NAME)
    educationProgressBarGameObject:findComponent("ProgressBar"):setValue(childInformation:getEducation())
    
    -- Happiness
    local happinessProgressBarGameObject = dialogGameObject:findChildGameObject(csd.HAPPINESS_PROGRESS_BAR_NAME)
    happinessProgressBarGameObject:findComponent("ProgressBar"):setValue(childInformation:getHappiness())
end

return csd