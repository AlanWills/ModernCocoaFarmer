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
local function toggleUI(caller, otherButtonName)
    caller:setActive(false)
    caller:setShouldRender(false)

    local otherButton = caller:getParent():findChildGameObject(otherButtonName)
    otherButton:setActive(true)
    otherButton:setShouldRender(true)

    -- This is a workaround for a stack panel bug
    -- Items changing render status do not get re-laid out
    caller:getParent():findComponent("StackPanel"):layout()
end

---------------------------------------------------------------------------------
local function play(eventArgs, caller, self)
    toggleUI(caller, TimePanel.PLAY_BUTTON_NAME)
    self._timeManager:play()
end

---------------------------------------------------------------------------------
local function pause(eventArgs, caller, self)
    toggleUI(caller, TimePanel.PAUSE_BUTTON_NAME)
    self._timeManager:pause()
end

---------------------------------------------------------------------------------
local function tryUpdateMonthText(eventArgs, self)
    self:setMonthText(self.MONTHS[self._timeManager:getCurrentMonth()])
end

---------------------------------------------------------------------------------
function TimePanel:new(timePanelGameObject, timeManager)
    self._monthText = timePanelGameObject:findChildGameObject(self.MONTH_TEXT_NAME):findComponent("TextRenderer")
    self._timeManager = timeManager
    tryUpdateMonthText(nil, self)

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, pause, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, play, self)

    timeManager:subscribeOnMonthPassedCallback(tryUpdateMonthText, self)
end

---------------------------------------------------------------------------------
function TimePanel:setMonthText(monthText)
    self._monthText:setText(monthText)
end

return TimePanel