local Class = require 'OOP.Class'
local ChildIcon = require 'UI.Family.ChildIcon'
local Algorithm = require 'Containers.Algorithm'

local FamilyPanel = {}
FamilyPanel.CHILD_STACK_PANEL = "ChildStackPanel"

---------------------------------------------------------------------------------
local function onChildAddedCallback(child, self)
    self:addChildIcon(child)
end

---------------------------------------------------------------------------------
function FamilyPanel:new(commandManager, dataStore, familyPanelGameObject)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._childStackPanel = familyPanelGameObject:findChild(self.CHILD_STACK_PANEL)
    self._childIcons = {}

    local familyManager = commandManager.familyManager

    for childCount = 0, (familyManager:getChildCount() - 1) do
        self:addChildIcon(familyManager:getChild(childCount))
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
    if child:isNotBorn() then
        -- Our child does not need an icon if it is not born
        return
    end

    local numChildren = Algorithm.tablelength(self._childIcons)
    log("Activating ChildIcon " .. tostring(numChildren))

    local childIconGameObject = self._childStackPanel:getChild(numChildren)
    self._childIcons[child:getName()] = Class.new(ChildIcon, self._commandManager, self._dataStore, childIconGameObject, child:getName())
    log("ChildIcon " .. tostring(numChildren) .. " activated")

    local familyPanelStackPanel = self._childStackPanel:findComponent("StackPanel"):layout()
end

return FamilyPanel