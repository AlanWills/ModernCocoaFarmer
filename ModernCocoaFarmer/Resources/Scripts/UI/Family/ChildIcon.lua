local Class = require 'OOP.Class'
local ToggleChildSelection = require 'Commands.Family.ToggleChildSelection'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_ACTIVE_IMAGE = "ChildActiveImage",
    CONSTANTS_NAME = "Constants",
    CHILD_ROOT_KEY_NAME = "ChildRootKey",
}

---------------------------------------------------------------------------------
local function childIconLeftClickedCallback(caller, self)
    self._commandManager:execute(ToggleChildSelection, self._childName)
end

---------------------------------------------------------------------------------
function ChildIcon:new(commandManager, gameObject, childName)
    self._commandManager = commandManager
    self._childName = childName

    gameObject:setName(childName)

    local childInteractionHandler = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClickedCallback, self)

    local childRootKeyGameObject = gameObject:findChild(self.CONSTANTS_NAME):findChild(self.CHILD_ROOT_KEY_NAME)
    childRootKeyGameObject:findComponent("Constant"):setValue(FamilyDataSources.CHILDREN .. "." .. childName)
end

return ChildIcon