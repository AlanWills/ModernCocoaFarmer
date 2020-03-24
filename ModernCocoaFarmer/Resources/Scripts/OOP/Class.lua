local Class = {}

---------------------------------------------------------------------------------
function Class.new(type, ...)
    if type.__index ~= type then
        type.__index = type
    end

    local instance = {}
    setmetatable(instance, type)

    if type.new ~= nil then
        instance:new(...)
    end

    return instance
end

---------------------------------------------------------------------------------
function Class.inheritsFrom(type)
    local new_class = {}
    local class_mt = { __index = new_class }

    if type then
        setmetatable(new_class, { __index = type })
    end

    return new_class
end

return Class