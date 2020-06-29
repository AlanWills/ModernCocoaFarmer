local Class = require 'OOP.Class'
local ModalDialogBase = require 'UI.Dialogs.ModalDialogBase'
local SendChildToLocation = require 'Commands.Locations.SendChildToLocation'
local DeselectChild = require 'Commands.Family.DeselectChild'

----------------------------------------------------------------------------------------
local LocationDialog = Class.inheritsFrom(ModalDialogBase)

LocationDialog.DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Locations", "LocationDialog.prefab")
LocationDialog.TITLE_TEXT_NAME = "TitleText"
LocationDialog.DESCRIPTION_TEXT_NAME = "DescriptionText"
LocationDialog.COST_ICON_NAME = "CostIcon"
LocationDialog.COST_TEXT_NAME = "CostText"
LocationDialog.TIME_ICON_NAME = "TimeIcon"
LocationDialog.TIME_TEXT_NAME = "TimeText"
LocationDialog.CLOSE_BUTTON_NAME = "CloseButton"
LocationDialog.LOCATION_STATS_NAME = "LocationStats"
LocationDialog.CHILD_STATS_NAME = "ChildStats"
LocationDialog.HEALTH_MODIFIER_TEXT_NAME = "HealthModifierText"
LocationDialog.SAFETY_MODIFIER_TEXT_NAME = "SafetyModifierText"
LocationDialog.EDUCATION_MODIFIER_TEXT_NAME = "EducationModifierText"
LocationDialog.HAPPINESS_MODIFIER_TEXT_NAME = "HappinessModifierText"
LocationDialog.SEND_CHILD_BACKGROUND_NAME = "SendChild"
LocationDialog.SEND_CHILD_HELP_TEXT_NAME = "SendChildHelpText"
LocationDialog.SEND_CHILD_BUTTON_NAME = "SendChildButton"
LocationDialog.SEND_CHILD_BUTTON_TEXT_NAME = "SendChildButtonText"
LocationDialog.CONSTANTS_NAME = "Constants"
LocationDialog.LOCATION_ROOT_KEY_NAME = "LocationRootKey"

----------------------------------------------------------------------------------------
function LocationDialog:new(commandManager, locationName)
    local dialogPrefab = Resources.loadPrefab(self.DIALOG_PREFAB_PATH)
    self._gameObject = dialogPrefab:instantiate()

    ModalDialogBase.new(self, commandManager, self._gameObject)

    self._dataStore = System.getDataSystem()
    self._locationName = locationName

    local locationRootKeyGameObject = self._gameObject:findChild(self.CONSTANTS_NAME):findChild(self.LOCATION_ROOT_KEY_NAME)
    locationRootKeyGameObject:findComponent("Constant"):setValue(datapath.combine(LocationsDataSources.LOCATIONS, locationName))

    self:setUpLocationInfoUI()
    self:setUpCloseButton()
    self:setUpModifierUI()
    self:setUpChildSelectionUI()
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
local function pluralize(quantity, str)
    if quantity > 1 then
        return str .. "s"
    else
        return str
    end
end

----------------------------------------------------------------------------------------
local function formatTimeString(daysToComplete)
    local years = math.floor(daysToComplete / 360)
    local months = math.floor((daysToComplete - 360 * years) / 30)
    local days = math.floor((daysToComplete - 360 * years - 30 * months))

    local timeString = ""

    if years > 0 then
        timeString = timeString .. tostring(years) .. " year"
        timeString = pluralize(years, timeString)
    end

    if months > 0 then
        timeString = timeString .. tostring(months) .. " month"
        timeString = pluralize(months, timeString)
    end

    if days > 0 then
        timeString = timeString .. tostring(days) .. " day"
        timeString = pluralize(days, timeString)
    end

    return timeString
end

----------------------------------------------------------------------------------------
local function formatModifierString(isDeltaChange, amount)
    local modifierText = "";

    if isDeltaChange then
        if amount >= 0 then
            modifierText = modifierText .. "+"
        end
    else
        modifierText = modifierText .. "set to "
    end

    modifierText = modifierText .. string.format("%d", amount)
    modifierText = modifierText .. "%"

    return modifierText
end

----------------------------------------------------------------------------------------
function LocationDialog:setUpLocationInfoUI()
    local locationKey = datapath.combine(LocationsDataSources.LOCATIONS, self._locationName)
    local locationDataObject = self._dataStore:getObject(locationKey)

    local locationStats = self._gameObject:findChild(self.LOCATION_STATS_NAME)
    local timeIcon = locationStats:findChild(self.TIME_ICON_NAME)
    local timeText = timeIcon:findChild(self.TIME_TEXT_NAME):findComponent("TextRenderer")
    timeText:setText(formatTimeString(locationDataObject:getUnsignedInt(LocationsDataSources.DAYS_TO_COMPLETE)))

    local moneyDataObject = self._dataStore:getObject(datapath.combine(locationKey, StatsDataSources.MONEY))
    
    local costIcon = locationStats:findChild(self.COST_ICON_NAME)
    local costText = costIcon:findChild(self.COST_TEXT_NAME):findComponent("TextRenderer")
    costText:setText(formatCostString(moneyDataObject:getFloat(StatsDataSources.AMOUNT)))
end

----------------------------------------------------------------------------------------
function LocationDialog.closeCallback(caller, self)
    self:hide()
end

----------------------------------------------------------------------------------------
function LocationDialog:setUpCloseButton()
    local closeButton = self._gameObject:findChild(self.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonUpCallback(LocationDialog.closeCallback, self)
end

----------------------------------------------------------------------------------------
function LocationDialog:setUpModifierUI()
    local locationKey = datapath.combine(LocationsDataSources.LOCATIONS, self._locationName)
    local locationStats = self._gameObject:findChild(self.LOCATION_STATS_NAME)
    local childStats = locationStats:findChild(self.CHILD_STATS_NAME)

    self:setModifierText(childStats, self.HEALTH_MODIFIER_TEXT_NAME, datapath.combine(locationKey, StatsDataSources.HEALTH))
    self:setModifierText(childStats, self.SAFETY_MODIFIER_TEXT_NAME, datapath.combine(locationKey, StatsDataSources.SAFETY))
    self:setModifierText(childStats, self.EDUCATION_MODIFIER_TEXT_NAME, datapath.combine(locationKey , StatsDataSources.EDUCATION))
    self:setModifierText(childStats, self.HAPPINESS_MODIFIER_TEXT_NAME, datapath.combine(locationKey , StatsDataSources.HAPPINESS))
end

----------------------------------------------------------------------------------------
function LocationDialog:setModifierText(stats, textName, modifierKey)
    local text = stats:findChild(textName):findComponent("TextRenderer")
    local modifierObject = self._dataStore:getObject(modifierKey)
    local isDeltaChange = modifierObject:getBool(StatsDataSources.IS_DELTA)
    local amount = modifierObject:getFloat(StatsDataSources.AMOUNT)

    text:setText(formatModifierString(isDeltaChange, amount))
end

----------------------------------------------------------------------------------------
function LocationDialog.sendChildToLocation(caller, self)
    local selectedChildName = self._dataStore:getString(FamilyDataSources.SELECTED_CHILD_NAME)
    self._commandManager:execute(SendChildToLocation, self._locationName, selectedChildName)
    self._commandManager:execute(DeselectChild, selectedChildName)
    self:hide()
end

----------------------------------------------------------------------------------------
function LocationDialog:setUpChildSelectionUI()
    local sendChildBackground = self._gameObject:findChild(self.SEND_CHILD_BACKGROUND_NAME)
    local sendChildHelpText = sendChildBackground:findChild(self.SEND_CHILD_HELP_TEXT_NAME)
    local sendChildButton = sendChildBackground:findChild(self.SEND_CHILD_BUTTON_NAME)

    local isChildSelected = self._dataStore:getBool(FamilyDataSources.HAS_SELECTED_CHILD)
    log("LocationDialog.isChildSelected " .. tostring(isChildSelected))

    local selectedChildName = self._dataStore:getString(FamilyDataSources.SELECTED_CHILD_NAME)
    local selectedChildObject = self._dataStore:getObject(datapath.combine(FamilyDataSources.CHILDREN, selectedChildName))

    local currentLocation = selectedChildObject:getString(FamilyDataSources.CURRENT_LOCATION)
    local isChildAlreadyAtLocation = isChildSelected and currentLocation ~= ""
    log("LocationDialog.isChildAlreadyAtLocation " .. tostring(isChildAlreadyAtLocation))

    local isChildAbleToBeSent = isChildSelected and not isChildAlreadyAtLocation
    log("LocationDialog.isChildAbleToBeSent " .. tostring(isChildAbleToBeSent))

    sendChildHelpText:setActive(not isChildAbleToBeSent)
    sendChildButton:setActive(isChildAbleToBeSent)
    
    if isChildAbleToBeSent then
        local sendChildButtonInteractionHandler = sendChildButton:findComponent("MouseInteractionHandler")
        sendChildButtonInteractionHandler:subscribeOnLeftButtonUpCallback(LocationDialog.sendChildToLocation, self)

        local sendChildButtonText = sendChildButton:findChild(self.SEND_CHILD_BUTTON_TEXT_NAME)
        sendChildButtonText:findComponent("TextRenderer"):setText("Send " .. selectedChildName)
    elseif isChildAlreadyAtLocation then
        sendChildHelpText:findComponent("TextRenderer"):setText(selectedChildName .. " is already at\nthe " .. currentLocation)
    else
        sendChildHelpText:findComponent("TextRenderer"):setText("Select a Child to send\nthem to this location")
    end
end

return LocationDialog
