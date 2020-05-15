local GameEventPeriod = require 'GameEvents.GameEventPeriod'

local GameEventManagerDolceWindow = 
{
    NAME = "Game Event Manager"
}

---------------------------------------------------------------------------------
function GameEventManagerDolceWindow:new(gameEventManager)
    self._gameEventManager = gameEventManager
    self._currentEvent = { NAME = "" }
    self._elapsedTime = 0
end

---------------------------------------------------------------------------------
function GameEventManagerDolceWindow:render()
    if ImGui.beginCombo("Game Event", self._currentEvent.NAME) then

        for timePeriod, events in pairs(self._gameEventManager._events) do
            for eventName, event in pairs(events) do
                local selectableChanged, isSelected = ImGui.selectable(eventName, self._currentEvent == event)
                if selectableChanged and isSelected then
                    self._currentEvent = event
                end
            end
        end

        ImGui.endCombo()
    end

    if self._currentEvent.NAME ~= "" then
        local commandManager = self._gameEventManager._commandManager
        local canTrigger = self._currentEvent.canTrigger == nil or self._currentEvent.canTrigger(commandManager)

        ImGui.text("CanTrigger: " .. tostring(canTrigger))

        local triggersEveryFrame = self._currentEvent.PERIOD == GameEventPeriod.EVERY_FRAME
        if triggersEveryFrame then
            self._elapsedTime = ImGui.inputFloat("Elapsed Time", self._elapsedTime)
        end

        if ImGui.button("Trigger") then
            if triggersEveryFrame then
                self._currentEvent.trigger(commandManager, self._elapsedTime)
            else
                self._currentEvent.trigger(commandManager)
            end
        end
    end
end

return GameEventManagerDolceWindow