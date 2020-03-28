local Class = require 'OOP.Class'
local ChildIcon = require 'UI.Family.ChildIcon'
local ToggleChildSelection = require 'Commands.Family.ToggleChildSelection'
local Algorithm = require 'Containers.Algorithm'

local FamilyPanel = {}

---------------------------------------------------------------------------------
local function childIconLeftClickedCallback(caller, extraArgs)
    extraArgs.self:toggleChildSelection(extraArgs.childToToggle)
end

---------------------------------------------------------------------------------
local function onChildAddedCallback(child, self)
    self:addChildIcon(child)
end

---------------------------------------------------------------------------------
function FamilyPanel:new(commandManager, dataStore, familyPanelGameObject)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._gameObject = familyPanelGameObject
    self._childIcons = {}

    commandManager.familyManager:subscribeOnChildAddedCallback(onChildAddedCallback, self)
end

---------------------------------------------------------------------------------
function FamilyPanel:updateUI()
    for k, childIcon in pairs(self._childIcons) do
        childIcon:updateUI()
    end
end

---------------------------------------------------------------------------------
function FamilyPanel:addChildIcon(child)
    local numChildren = Algorithm.tablelength(self._childIcons)
    log("Activating ChildIcon " .. tostring(numChildren))

    local childIconGameObject = self._gameObject:getChild(numChildren)
    self._childIcons[child:getName()] = Class.new(ChildIcon, self._dataStore, childIconGameObject, child)
    log("ChildIcon " .. tostring(numChildren) .. " activated")

    local childInteractionHandler = childIconGameObject:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClickedCallback, { self = self, childToToggle = child })

    local familyPanelStackPanel = self._gameObject:findComponent("StackPanel"):layout()
end

---------------------------------------------------------------------------------
function FamilyPanel:toggleChildSelection(child)
    self._commandManager:execute(ToggleChildSelection, child)
end

return FamilyPanel