local Class = require 'OOP.Class'
local EventNotification = require 'UI.Events.EventNotification'
local PayBills = require 'Events.PayBills'

local GameEventManager = {}

---------------------------------------------------------------------------------
local function onDayPassed(self)
    -- Trigger appropriate events
end

---------------------------------------------------------------------------------
local function onMonthPassed(self)
    -- Trigger appropriate events
    if self._state.timeManager:getMonthIndex() == 4 then
        self:triggerEvent(PayBills)
    end
end

---------------------------------------------------------------------------------
local function onYearPassed(self)
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

    timeManager:subscribeOnDayPassedCallback("GameEventManager_OnDayPassed", onDayPassed, self)
    timeManager:subscribeOnMonthPassedCallback("GameEventManager_OnMonthPassed", onMonthPassed, self)
    timeManager:subscribeOnYearPassedCallback("GameEventManager_OnYearPassed", onYearPassed, self)
end

---------------------------------------------------------------------------------
function GameEventManager:triggerEvent(event)
    local eventInstance = Class.new(event)

    if eventInstance.canExecute == nil or eventInstance:canExecute(self._state) then
        if eventInstance.execute ~= nil then
            eventInstance:execute(self._state)
        end

        -- Create notification prefab
        local notification = Class.new(EventNotification, self._eventNotificationsGameObject:getScreen(), eventInstance)
        self._eventNotificationsGameObject:findComponent("StackPanel"):addChild(notification.gameObject)
    end
end

return GameEventManager