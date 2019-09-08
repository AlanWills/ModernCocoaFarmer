local InteractableBuildingDialog = require "UI.InteractableBuildingDialog"

local ibm = {}

----------------------------------------------------------------------------------------
ibm.INTERACTABLE_BUILDINGS_NAME = "InteractableBuildings"
ibm.SCHOOL_NAME = "School";
ibm.SCHOOL_PATH = "Data\\Buildings\\School.asset"

----------------------------------------------------------------------------------------
local function schoolClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.SCHOOL_PATH));
end

----------------------------------------------------------------------------------------
local function setUpBuilding(managerGameObject, gameObjectName, gameObjectPath, buildingClickedCallback)
    local building = managerGameObject:findChildGameObject(gameObjectName)
    local icon = building:findChildGameObject("Icon")
    local interactionHandler = icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonClickedCallback(buildingClickedCallback)
end

----------------------------------------------------------------------------------------
function ibm.initialize(screen)
    local managerGameObject = screen:findGameObject(ibm.INTERACTABLE_BUILDINGS_NAME)
    
    -- School
    setUpBuilding(managerGameObject, ibm.SCHOOL_NAME, ibm.SCHOOL_PATH, schoolClickedCallback)
end

return ibm