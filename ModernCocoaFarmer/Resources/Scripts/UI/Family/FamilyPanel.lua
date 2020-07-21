local Class = require 'OOP.Class'
local ChildIcon = require 'UI.Family.ChildIcon'
local Algorithm = require 'Containers.Algorithm'
local ToggleChildSelection = require 'Commands.Family.ToggleChildSelection'

local FamilyPanel = {}
FamilyPanel.CHILD_STACK_PANEL = "ChildStackPanel"

---------------------------------------------------------------------------------
function FamilyPanel:new(commandManager, familyPanelGameObject)
    self._commandManager = commandManager
    self._childStackPanel = familyPanelGameObject:findChild(self.CHILD_STACK_PANEL)
    self._childIcons = {}
    self._selectChildHandle = Keyboard.subscribeOnKeyPressedCallback(FamilyPanel.selectChildCallback, self)

    local familyManager = commandManager.familyManager

    for childCount = 0, (familyManager:getChildCount() - 1) do
        self:addChildIcon(familyManager:getChild(childCount))
    end

    familyManager:subscribeOnChildAddedCallback(FamilyPanel.onChildAddedCallback, self)
end

---------------------------------------------------------------------------------
function FamilyPanel:destroy()
    Keyboard.unsubscribeOnKeyPressedCallback(self._selectChildHandle)
end

---------------------------------------------------------------------------------
function FamilyPanel.selectChildCallback(key, self)
    if Key.isNumber(key) then
        local number = Key.getNumber(key)
        local familyManager = self._commandManager.familyManager
        
        if number > 0 and number <= familyManager:getChildCount() and familyManager:getChild(number - 1):isActivated() then
           self._commandManager:execute(ToggleChildSelection, familyManager:getChild(number - 1):getName())
        end
    end
end

---------------------------------------------------------------------------------
function FamilyPanel.onChildAddedCallback(child, self)
    self:addChildIcon(child)
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
    self._childIcons[child:getName()] = Class.new(ChildIcon, self._commandManager, childIconGameObject, child:getName())
    log("ChildIcon " .. tostring(numChildren) .. " activated")

    local familyPanelStackPanel = self._childStackPanel:findComponent("StackPanel"):layout()
end

return FamilyPanel