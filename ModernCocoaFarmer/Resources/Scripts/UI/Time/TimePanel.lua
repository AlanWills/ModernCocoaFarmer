local Play = require 'Commands.Time.Play'
local Pause = require 'Commands.Time.Pause'

---------------------------------------------------------------------------------
local TimePanel = 
{
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
function TimePanel:new(commandManager, timePanelGameObject)
    self._commandManager = commandManager

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, play, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, pause, self)
end

return TimePanel