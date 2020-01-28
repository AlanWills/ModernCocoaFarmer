---------------------------------------------------------------------------------
local TimePanel = 
{
    MONTH_TEXT_NAME = "MonthText",
    PLAY_BUTTON_NAME = "PlayButton",
    PAUSE_BUTTON_NAME = "PauseButton",
    MONTHS = 
    {
        [0] = "January",
        [1] = "February",
        [2] = "March",
        [3] = "April",
        [4] = "May",
        [5] = "June",
        [6] = "July",
        [7] = "August",
        [8] = "September",
        [9] = "October",
        [10] = "November",
        [11] = "December"
    }
}

---------------------------------------------------------------------------------
local function setUIEnabledAndOtherDisabled(caller, otherButtonName)
    caller:findComponent("SpriteRenderer"):setColour(0.2, 1, 0.2)

    local otherButton = caller:getParent():findChildGameObject(otherButtonName)
    otherButton:findComponent("SpriteRenderer"):setColour(1, 1, 1)
end

---------------------------------------------------------------------------------
local function play(caller, self)
    setUIEnabledAndOtherDisabled(caller, TimePanel.PAUSE_BUTTON_NAME)
    self._timeManager:play()
end

---------------------------------------------------------------------------------
local function pause(caller, self)
    setUIEnabledAndOtherDisabled(caller, TimePanel.PLAY_BUTTON_NAME)
    self._timeManager:pause()
end

---------------------------------------------------------------------------------
function TimePanel:new(timeManager, timePanelGameObject)
    self._monthText = timePanelGameObject:findChildGameObject(self.MONTH_TEXT_NAME):findComponent("TextRenderer")
    self._timeManager = timeManager

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, play, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, pause, self)
end

---------------------------------------------------------------------------------
function TimePanel:updateUI()
    self:setMonthText(self.MONTHS[self._timeManager:getCurrentMonth()])
end

---------------------------------------------------------------------------------
function TimePanel:setMonthText(monthText)
    self._monthText:setText(monthText)
end

return TimePanel