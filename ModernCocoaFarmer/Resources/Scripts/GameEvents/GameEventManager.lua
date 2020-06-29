local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local GetPaidSalary = require 'GameEvents.Money.GetPaidSalary'
local PayBills = require 'GameEvents.Money.PayBills'
local SalaryIncreased = require 'GameEvents.Money.SalaryIncreased'
local SalaryDecreased = require 'GameEvents.Money.SalaryDecreased'
local AddFirstChild = require 'GameEvents.Family.AddFirstChild'
local TryAddChild = require 'GameEvents.Family.TryAddChild'
local ApplyFamilyModifiers = require 'GameEvents.Family.ApplyFamilyModifiers'
local UpdateChildrenStates = require 'GameEvents.Family.UpdateChildrenStates'
local UpdateChildrenTimes = require 'GameEvents.Locations.UpdateChildrenTimes'
local ApplyLocationModifiers = require 'GameEvents.Locations.ApplyLocationModifiers'
local CheckForChildrenLeaving = require 'GameEvents.Locations.CheckForChildrenLeaving'
local ChildExpelledFromSchool = require 'GameEvents.Locations.ChildExpelledFromSchool'
local WelcomeToZegoua = require 'GameEvents.OneUse.WelcomeToZegoua'
local UNPeaceKeepersArrive = require 'GameEvents.OneUse.UNPeaceKeepersArrive'

local GameEventManager = {}

---------------------------------------------------------------------------------
function GameEventManager.onTimePassedCallback(elapsedWorldTime, gameEventManager)
    gameEventManager:onTimePassed(elapsedWorldTime)
end

---------------------------------------------------------------------------------
function GameEventManager.onDayPassedCallback(gameEventManager)
    gameEventManager:onDayPassed()
end

---------------------------------------------------------------------------------
function GameEventManager.onMonthPassedCallback(gameEventManager)
    gameEventManager:onMonthPassed()
end

---------------------------------------------------------------------------------
function GameEventManager.onYearPassedCallback(gameEventManager)
    gameEventManager:onYearPassed()
end

---------------------------------------------------------------------------------
function GameEventManager:new(commandManager)
    self._commandManager = commandManager
    self._events = {}
    
    for k, v in pairs(GameEventPeriod) do
        self._events[v] = {}
    end

    local timeManager = self._commandManager.timeManager
    timeManager:subscribeOnTimePassedCallback(GameEventManager.onTimePassedCallback, self)
    timeManager:subscribeOnDayPassedCallback(GameEventManager.onDayPassedCallback, self)
    timeManager:subscribeOnMonthPassedCallback(GameEventManager.onMonthPassedCallback, self)
    timeManager:subscribeOnYearPassedCallback(GameEventManager.onYearPassedCallback, self)

    -- Event Initialization
    self:registerEvent(GetPaidSalary)
    self:registerEvent(PayBills)
    self:registerEvent(SalaryIncreased)
    self:registerEvent(SalaryDecreased)
    self:registerEvent(AddFirstChild)
    self:registerEvent(TryAddChild)
    self:registerEvent(ApplyFamilyModifiers)
    self:registerEvent(UpdateChildrenStates)
    self:registerEvent(UpdateChildrenTimes)
    self:registerEvent(ApplyLocationModifiers)
    self:registerEvent(CheckForChildrenLeaving)
    self:registerEvent(ChildExpelledFromSchool)
    self:registerEvent(WelcomeToZegoua)
    self:registerEvent(UNPeaceKeepersArrive)
end

---------------------------------------------------------------------------------
function GameEventManager:registerEvent(event)
    self._events[event.PERIOD][event.NAME] = event
end

---------------------------------------------------------------------------------
function GameEventManager:tryTriggerEvents(period, ...)
    for eventName, event in pairs(self._events[period]) do
        if event.canTrigger == nil or event.canTrigger(self._commandManager) then
            event.trigger(self._commandManager, ...)
        end
    end
end

---------------------------------------------------------------------------------
function GameEventManager:onTimePassed(elapsedWorldTime)
    self:tryTriggerEvents(GameEventPeriod.EVERY_FRAME, elapsedWorldTime)
end

---------------------------------------------------------------------------------
function GameEventManager:onDayPassed()
    self:tryTriggerEvents(GameEventPeriod.EVERY_DAY)
end

---------------------------------------------------------------------------------
function GameEventManager:onMonthPassed()
    self:tryTriggerEvents(GameEventPeriod.EVERY_MONTH)
end

---------------------------------------------------------------------------------
function GameEventManager:onYearPassed()
    self:tryTriggerEvents(GameEventPeriod.EVERY_YEAR)
end

return GameEventManager