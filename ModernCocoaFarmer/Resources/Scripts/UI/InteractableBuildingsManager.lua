local InteractableBuildingDialog = require "UI.InteractableBuildingDialog"

local ibm = {}

----------------------------------------------------------------------------------------
ibm.INTERACTABLE_BUILDINGS_NAME = "InteractableBuildings"

----------------------------------------------------------------------------------------
ibm.HOME_NAME = "Home";
ibm.HOME_PATH = "Data\\Buildings\\Home.asset"

----------------------------------------------------------------------------------------
ibm.HOSPITAL_NAME = "Hospital";
ibm.HOSPITAL_PATH = "Data\\Buildings\\Hospital.asset"

----------------------------------------------------------------------------------------
ibm.MARKET_NAME = "Market";
ibm.MARKET_PATH = "Data\\Buildings\\Market.asset"

----------------------------------------------------------------------------------------
ibm.MOSQUE_NAME = "Mosque";
ibm.MOSQUE_PATH = "Data\\Buildings\\Mosque.asset"

----------------------------------------------------------------------------------------
ibm.SCHOOL_NAME = "School";
ibm.SCHOOL_PATH = "Data\\Buildings\\School.asset"

----------------------------------------------------------------------------------------
ibm.WELL_NAME = "Well";
ibm.WELL_PATH = "Data\\Buildings\\Well.asset"

----------------------------------------------------------------------------------------
local function homeClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.HOME_PATH));
end

----------------------------------------------------------------------------------------
local function hospitalClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.HOSPITAL_PATH));
end

----------------------------------------------------------------------------------------
local function marketClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.MARKET_PATH));
end

----------------------------------------------------------------------------------------
local function mosqueClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.MOSQUE_PATH));
end

----------------------------------------------------------------------------------------
local function schoolClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.SCHOOL_PATH));
end

----------------------------------------------------------------------------------------
local function wellClickedCallback(e, caller)
    InteractableBuildingDialog.show(caller:getScreen(), BuildingInformation.load(ibm.WELL_PATH));
end

----------------------------------------------------------------------------------------
local function setUpBuilding(managerGameObject, gameObjectName, gameObjectPath, buildingClickedCallback)
    local building = managerGameObject:findChildGameObject(gameObjectName)
    local icon = building:findChildGameObject("Icon")
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonClickedCallback(buildingClickedCallback)
end

----------------------------------------------------------------------------------------
function ibm.initialize(screen)
    local managerGameObject = screen:findGameObject(ibm.INTERACTABLE_BUILDINGS_NAME)
    
    -- Home
    setUpBuilding(managerGameObject, ibm.HOME_NAME, ibm.HOME_PATH, homeClickedCallback)

    -- Hospital
    setUpBuilding(managerGameObject, ibm.HOSPITAL_NAME, ibm.HOSPITAL_PATH, hospitalClickedCallback)

    -- Market
    setUpBuilding(managerGameObject, ibm.MARKET_NAME, ibm.MARKET_PATH, marketClickedCallback)

    -- Mosque
    setUpBuilding(managerGameObject, ibm.MOSQUE_NAME, ibm.MOSQUE_PATH, mosqueClickedCallback)

    -- School
    setUpBuilding(managerGameObject, ibm.SCHOOL_NAME, ibm.SCHOOL_PATH, schoolClickedCallback)

    -- Well
    setUpBuilding(managerGameObject, ibm.WELL_NAME, ibm.WELL_PATH, wellClickedCallback)
end

return ibm