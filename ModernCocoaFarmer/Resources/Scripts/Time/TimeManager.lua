local Class = require 'OOP.Class'
local Event = require 'Events.Event'

local TimeManager =
{
    Months = 
    {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    }
}

---------------------------------------------------------------------------------
function TimeManager:new(timeComponent)
    self._timeComponent = timeComponent
    self._monthIndex = 1
end

---------------------------------------------------------------------------------
function TimeManager:getMonthString()
    return self.Months[self._monthIndex]
end

return TimeManager