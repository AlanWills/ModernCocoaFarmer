---------------------------------------------------------------------------------
local TimePanel = 
{
    MONTH_TEXT_NAME = "MonthText",
    PLAY_BUTTON_NAME = "PlayButton",
    PAUSE_BUTTON_NAME = "PauseButton"
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
local function tryUpdateMonthText(self)
    self:setMonthText(self._timeManager:getMonthString())
end

---------------------------------------------------------------------------------
function TimePanel:new(timePanelGameObject, timeManager)
    self._monthText = timePanelGameObject:findChildGameObject(self.MONTH_TEXT_NAME):findComponent("TextRenderer")
    self._timeManager = timeManager
    tryUpdateMonthText(self)

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, pause, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, play, self)

    timeManager:subscribeOnMonthPassedCallback("TimeManager_OnMonthPassed", tryUpdateMonthText, self)
end

---------------------------------------------------------------------------------
function TimePanel:setMonthText(monthText)
    self._monthText:setText(monthText)
end

return TimePanel