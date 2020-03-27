local AddChild = {}

---------------------------------------------------------------------------------
function AddChild:execute(commandManager)
    log("Adding child to family manager")
    commandManager.familyManager:addChild()
end

return AddChild