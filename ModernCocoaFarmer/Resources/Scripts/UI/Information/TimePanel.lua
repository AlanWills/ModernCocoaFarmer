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
local function play(eventArgs, caller)
    toggleUI(caller, TimePanel.PLAY_BUTTON_NAME)
end

---------------------------------------------------------------------------------
local function pause(eventArgs, caller)
    toggleUI(caller, TimePanel.PAUSE_BUTTON_NAME)
end

---------------------------------------------------------------------------------
function TimePanel:new(timePanelGameObject)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, pause)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, play)
end

return TimePanel