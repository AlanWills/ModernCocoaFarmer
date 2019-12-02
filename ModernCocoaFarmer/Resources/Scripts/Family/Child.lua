local child = {}
child.__index = child

---------------------------------------------------------------------------------
function child.create(childInformation)
    local c = {}
    setmetatable(c, child)

    c.childInformation = childInformation
    c.name = childInformation:getName()
    return c
end

return child