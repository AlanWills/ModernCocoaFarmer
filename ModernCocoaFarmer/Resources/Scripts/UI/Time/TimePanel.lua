local Play = require 'Commands.Time.Play'
local Pause = require 'Commands.Time.Pause'

---------------------------------------------------------------------------------
local TimePanel = 
{
    PLAY_BUTTON_NAME = "PlayButton",
    PAUSE_BUTTON_NAME = "PauseButton"
}

---------------------------------------------------------------------------------
function TimePanel.play(caller, self)
    self._commandManager:execute(Play)
end

---------------------------------------------------------------------------------
function TimePanel.pause(caller, self)
    self._commandManager:execute(Pause)
end

---------------------------------------------------------------------------------
function TimePanel:new(commandManager, timePanelGameObject)
    self._commandManager = commandManager

    timePanelGameObject:setupChildLeftButtonUpCallback(self.PLAY_BUTTON_NAME, TimePanel.play, self)
    timePanelGameObject:setupChildLeftButtonUpCallback(self.PAUSE_BUTTON_NAME, TimePanel.pause, self)
end

return TimePanel