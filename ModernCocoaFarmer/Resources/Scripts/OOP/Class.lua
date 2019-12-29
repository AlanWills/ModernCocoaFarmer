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

return Class