local TimeManagerDolceWindow = 
{
    NAME = "Time Manager"
}

---------------------------------------------------------------------------------
function TimeManagerDolceWindow:new(timeManager)
    self._timeManager = timeManager
end

---------------------------------------------------------------------------------
function TimeManagerDolceWindow:render()
    self._timeManager:setPaused(ImGui.checkbox("Is Paused", self._timeManager:isPaused()))
    self._timeManager:setSecondsPerDay(ImGui.inputFloat("Seconds Per Day", self._timeManager:getSecondsPerDay()))

    local secondsPerDay = self._timeManager:getSecondsPerDay()

    local newCurrentDay, currentDayChanged = ImGui.inputUInt("Current Day", self._timeManager:getCurrentDay())
    if currentDayChanged and newCurrentDay <= 30 then
        self._timeManager:update((newCurrentDay - self._timeManager:getCurrentDay()) * secondsPerDay)
    end

    local newCurrentMonth, currentMonthChanged = ImGui.inputUInt("Current Month", self._timeManager:getCurrentMonth())
    if currentMonthChanged and newCurrentMonth <= 12 then
        self._timeManager:update((newCurrentMonth - self._timeManager:getCurrentMonth()) * secondsPerDay * 30)
    end

    local newCurrentYear, currentYearChanged = ImGui.inputUInt("Current Year", self._timeManager:getCurrentYear())
    if currentYearChanged then
        self._timeManager:update((newCurrentYear - self._timeManager:getCurrentYear()) * secondsPerDay * 360)
    end
end

return TimeManagerDolceWindow