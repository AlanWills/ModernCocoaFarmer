local Class = require 'OOP.Class'
local Event = require 'Events.Event'

local TimeManager =
{
    MONTHS = 
    {
        [1] = "January",
        [2] = "February",
        [3] = "March",
        [4] = "April",
        [5] = "May",
        [6] = "June",
        [7] = "July",
        [8] = "August",
        [9] = "September",
        [10] = "October",
        [11] = "November",
        [12] = "December"
    },
    TIME_PER_DAY = 1,
    TIME_PER_MONTH = 30,
    DEFAULT_TIME_MULTIPLIER = 1
}

---------------------------------------------------------------------------------
local function onTimeChanged(eventArgs, deltaTime, self)
    if not self._paused then
        self._dayDelta = self._dayDelta + deltaTime * self._timeMultiplier
        self._monthDelta = self._monthDelta + deltaTime * self._timeMultiplier

        self:tryUpdateDay()
        self:tryUpdateMonth()
    end
end

---------------------------------------------------------------------------------
function TimeManager:new(timeNotifier)
    self._timeNotifier = timeNotifier
    self._paused = false
    self._monthIndex = 1
    self._dayDelta = 0
    self._monthDelta = 0
    self._timeMultiplier = self.DEFAULT_TIME_MULTIPLIER
    self._timeNotifier:subscribeOnTimeChangedCallback(onTimeChanged, self)
    self._onDayPassed = Class.new(Event)
    self._onMonthPassed = Class.new(Event)
    self._onYearPassed = Class.new(Event)
end

---------------------------------------------------------------------------------
function TimeManager:getMonthIndex()
    return self._monthIndex
end

---------------------------------------------------------------------------------
function TimeManager:getMonthString()
    return self.MONTHS[self._monthIndex]
end

---------------------------------------------------------------------------------
function TimeManager:play()
    self._paused = false
end

---------------------------------------------------------------------------------
function TimeManager:pause()
    self._paused = true
end

---------------------------------------------------------------------------------
function TimeManager:tryUpdateDay()
    while self._dayDelta >= self.TIME_PER_DAY do
        self._dayDelta = self._dayDelta - self.TIME_PER_DAY
        self._onDayPassed:invoke()
    end
end

---------------------------------------------------------------------------------
function TimeManager:tryUpdateMonth()
    while self._monthDelta >= self.TIME_PER_MONTH do
        self._monthDelta = self._monthDelta - self.TIME_PER_MONTH
        self._monthIndex = ((self._monthIndex % 12) + 1) -- One indexed!
        self._onMonthPassed:invoke()

        if self._monthIndex == 0 then
            self._onYearPassed:invoke()
        end
    end
end

---------------------------------------------------------------------------------
function TimeManager:subscribeOnDayPassedCallback(name, callback, extraArgs)
    self._onDayPassed:subscribe(name, callback, extraArgs)
end

---------------------------------------------------------------------------------
function TimeManager:subscribeOnMonthPassedCallback(name, callback, extraArgs)
    self._onMonthPassed:subscribe(name, callback, extraArgs)
end

---------------------------------------------------------------------------------
function TimeManager:subscribeOnYearPassedCallback(name, callback, extraArgs)
    self._onYearPassed:subscribe(name, callback, extraArgs)
end

return TimeManager