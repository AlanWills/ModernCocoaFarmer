local AddChild = {}

---------------------------------------------------------------------------------
function AddChild:execute(state)
    log("Adding child to family manager")
    state.familyManager:addChild()
end

return AddChild