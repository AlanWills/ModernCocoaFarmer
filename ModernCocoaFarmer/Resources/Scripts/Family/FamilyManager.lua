local Class = require 'OOP.Class'
local Child = require 'Family.Child'

local Family = {}

---------------------------------------------------------------------------------
function Family:new()
    self.children = {}
    
    local i = 1
    
    while i <= 7 do
        local childInformation = ChildInformation.create("Child " .. i)
        self.children[i] = Class.new(Child, childInformation)

        i = i + 1
    end
end

return Family