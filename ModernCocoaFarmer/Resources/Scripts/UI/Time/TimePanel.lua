local Play = require 'Commands.Time.Play'
local Pause = require 'Commands.Time.Pause'

---------------------------------------------------------------------------------
local TimePanel = 
{
    MONTH_TEXT_NAME = "MonthText",
    PLAY_BUTTON_NAME = "PlayButton",
    PAUSE_BUTTON_NAME = "PauseButton"
}

---------------------------------------------------------------------------------
local function play(caller, self)
    self._commandManager:execute(Play)
end

---------------------------------------------------------------------------------
local function pause(caller, self)
    self._commandManager:execute(Pause)
end

---------------------------------------------------------------------------------
function TimePanel:new(commandManager, dataStore, timePanelGameObject)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._monthText = timePanelGameObject:findChild(self.MONTH_TEXT_NAME):findComponent("TextRenderer")
    self._playButtonRenderer = timePanelGameObject:findChild(self.PLAY_BUTTON_NAME):findComponent("SpriteRenderer")
    self._pauseButtonRenderer = timePanelGameObject:findChild(self.PAUSE_BUTTON_NAME):findComponent("SpriteRenderer")

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, play, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, pause, self)
end

---------------------------------------------------------------------------------
function TimePanel:updateUI()
    self:setTimeButtonColours(self._dataStore:getBool(TimeDataSources.IS_PAUSED))
end

---------------------------------------------------------------------------------
function TimePanel:setTimeButtonColours(isPaused)
    if isPaused then
        self._playButtonRenderer:setColour(0.4,0.4,0.4)
        self._pauseButtonRenderer:setColour(0.35,0.7,0)
    else
        self._pauseButtonRenderer:setColour(0.4,0.4,0.4)
        self._playButtonRenderer:setColour(0.35,0.7,0)
    end
end

return TimePanel