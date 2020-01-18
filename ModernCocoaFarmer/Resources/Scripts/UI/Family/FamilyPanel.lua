local Class = require 'OOP.Class'
local ChildIcon = require 'UI.Family.ChildIcon'

local FamilyPanel = {}

---------------------------------------------------------------------------------
local function childIconLeftClickedCallback(eventArgs, caller, extraArgs)
    extraArgs.self:selectChildIcon(extraArgs.childToSelect)
end

---------------------------------------------------------------------------------
local function onChildAddedCallback(eventArgs, child, self)
    self:addChildIcon(child)
end

---------------------------------------------------------------------------------
function FamilyPanel:new(familyManager, familyPanelGameObject)
    self._familyManager = familyManager
    self._gameObject = familyPanelGameObject
    self._childIcons = {}

    local childCount = 0
    while childCount < familyManager:getChildCount() do
        self:addChildIcon(familyManager:getChild(childCount))
        childCount = childCount + 1
    end
    
    familyManager:subscribeOnChildAddedCallback(onChildAddedCallback, self)
end

---------------------------------------------------------------------------------
function FamilyPanel:updateUI()
    for k, childIcon in pairs(self._childIcons) do
        childIcon:updateUI()
    end
end

---------------------------------------------------------------------------------
function FamilyPanel:addChildIcon(child)
    local childIcon = Class.new(ChildIcon, self._gameObject, child)
    self._childIcons[child:getName()] = childIcon

    local childInteractionHandler = childIcon.gameObject:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClickedCallback, { self = self, childToSelect = child })
end

---------------------------------------------------------------------------------
function FamilyPanel:selectChildIcon(child)
    self._familyManager:selectOnlyThisChild(child)
end

return FamilyPanel