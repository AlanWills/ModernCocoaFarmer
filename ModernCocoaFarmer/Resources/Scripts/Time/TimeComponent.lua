local Class = require 'OOP.Class'
local Event = require 'Events.Event'

---------------------------------------------------------------------------------
local TimeComponent = {}

---------------------------------------------------------------------------------
function TimeComponent:onInitialize()
    self._onTimeChanged = Class.new(Event)
end

---------------------------------------------------------------------------------
function TimeComponent:onUpdate(deltaTime)
    self._onTimeChanged:invoke(deltaTime)
end

---------------------------------------------------------------------------------
function TimeComponent:subscribeOnTimeChangedCallback(name, callback, extraArgs)
    self._onTimeChanged:subscribe(name, callback, extraArgs)
end

--registerComponent("TimeComponent", TimeComponent)