local Event = {}

---------------------------------------------------------------------------------
function Event:new()
    self.subscribers = {}
end

---------------------------------------------------------------------------------
function Event:subscribe(name, callback, extraArgs)
    if self.subscribers.name == nil then
        local event = {}
        event._callback = callback
        event._extraArgs = extraArgs

        self.subscribers[name] = event
    end
end

---------------------------------------------------------------------------------
function Event:unsubscribe(name)
    if self.subscribers.name ~= nil then
        -- Do we need to do both here?  When we unit test we can see
        self.subscribers[name] = nil
        self.subscribers.name = nil
    end
end

---------------------------------------------------------------------------------
function Event:invoke(...)
    for k, event in pairs(self.subscribers) do
        event._callback(event._extraArgs, ...)
    end
end

return Event