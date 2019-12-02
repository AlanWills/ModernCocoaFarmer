local child = require 'Family.Child'

local family = {}

---------------------------------------------------------------------------------
function family.initialize()
    family.children = {}
    local i = 1
    
    while i <= 7 do
        local childInformation = ChildInformation.create("Child " .. i)
        family.children[i] = child.create(childInformation)

        i = i + 1
    end
end

return family