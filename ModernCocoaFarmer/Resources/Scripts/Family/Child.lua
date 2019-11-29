local child = {}

---------------------------------------------------------------------------------
function child.initialize(childInformation)
    child.childInformation = childInformation
    child.name = childInformation:getName()
end

return child