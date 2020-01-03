local Class = require 'OOP.Class'
local EventNotification = require 'UI.Events.EventNotification'
local PayBills = require 'Events.PayBills'

local GameEventManager = {}

---------------------------------------------------------------------------------
local function onDayPassed(eventArgs, self)
    -- Trigger appropriate events
end

---------------------------------------------------------------------------------
local function onMonthPassed(eventArgs, self)
    -- Trigger appropriate events
    if self._state.timeManager:getCurrentMonth() == 3 then
        self:triggerEvent(PayBills)
    end
end

---------------------------------------------------------------------------------
local function onYearPassed(eventArgs, self)
    -- Trigger appropriate events
end

---------------------------------------------------------------------------------
function GameEventManager:new(eventNotificationsGameObject, familyManager, moneyManager, timeManager)
    self._eventNotificationsGameObject = eventNotificationsGameObject

    local state = {}
    state.familyManager = familyManager
    state.moneyManager = moneyManager
    state.timeManager = timeManager
    self._state = state;

    timeManager:subscribeOnDayPassedCallback(onDayPassed, self)
    timeManager:subscribeOnMonthPassedCallback(onMonthPassed, self)
    timeManager:subscribeOnYearPassedCallback(onYearPassed, self)
end

---------------------------------------------------------------------------------
function GameEventManager:triggerEvent(event)
    local eventInstance = Class.new(event)

    if eventInstance.canExecute == nil or eventInstance:canExecute(self._state) then
        if eventInstance.execute ~= nil then
            eventInstance:execute(self._state)
        end

        -- Move this to separate UI class that hooks into GameEventManager on event triggered
        local notification = Class.new(EventNotification, self._eventNotificationsGameObject:getScreen(), eventInstance)
        self._eventNotificationsGameObject:findComponent("StackPanel"):addChild(notification.gameObject)
    end
end

return GameEventManager