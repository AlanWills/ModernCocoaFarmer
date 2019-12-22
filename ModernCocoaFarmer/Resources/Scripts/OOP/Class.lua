local Class = {}

---------------------------------------------------------------------------------
function Class.declare()
    local class = {}
    class.__index = class

    return class
end

---------------------------------------------------------------------------------
function Class.new(type)
    local instance = {}
    setmetatable(instance, type)

    return instance
end

return Class