local Class = require 'OOP.Class'
local GameEventNotification = require 'UI.Events.GameEventNotification'

local GameEventsBar = {}

---------------------------------------------------------------------------------
local function createNotification(eventArgs, gameEvent, self)
    local notification = Class.new(GameEventNotification, self._gameObject:getScreen(), gameEvent)
    self._gameObject:findComponent("StackPanel"):addChild(notification.gameObject)
end

---------------------------------------------------------------------------------
function GameEventsBar:new(gameEventBarGameObject, gameEventManager)
    self._gameObject = gameEventBarGameObject

    gameEventManager:subscribeOnGameEventTriggeredCallback(createNotification, self)
end

return GameEventsBar