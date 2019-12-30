local GameEventManager = {}

---------------------------------------------------------------------------------
local function onDayPassed(self)
end

---------------------------------------------------------------------------------
local function onMonthPassed(self)
end

---------------------------------------------------------------------------------
local function onYearPassed(self)
end

---------------------------------------------------------------------------------
function GameEventManager:new(eventNotificationsGameObject, timeManager)
    self._eventNotificationsGameObject = eventNotificationsGameObject

    timeManager:subscribeOnDayPassedCallback("GameEventManager_OnDayPassed", onDayPassed, self)
    timeManager:subscribeOnMonthPassedCallback("GameEventManager_OnMonthPassed", onMonthPassed, self)
    timeManager:subscribeOnYearPassedCallback("GameEventManager_OnYearPassed", onYearPassed, self)
end

return GameEventManager


-- Welcome to zegoua is queued up at start
-- Have list of game events that can be triggered
-- Validate each one on time manager time events
-- If event should be triggered, create notification prefab and do event
-- Right click to squelch notifications