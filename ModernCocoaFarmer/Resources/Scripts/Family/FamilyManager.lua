local Class = require 'OOP.Class'
local Child = require 'Family.Child'

local Family = Class.declare()

---------------------------------------------------------------------------------
function Family.new()
    local family = Class.new(Family)
    family.children = {}
    
    local i = 1
    
    while i <= 7 do
        local childInformation = ChildInformation.create("Child " .. i)
        family.children[i] = Child.new(childInformation)

        i = i + 1
    end

    return family
end

return Family