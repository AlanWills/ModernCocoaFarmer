local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local FinishGame = require 'Commands.State.FinishGame'

local CheckForGameEnd = {}

---------------------------------------------------------------------------------
function CheckForGameEnd.canExecute(commandManager)
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isActivated() or child:isNotBorn() then
            -- Game is not over if one child remains alive
            return false
        end
    end

    return true
end

---------------------------------------------------------------------------------
function CheckForGameEnd.execute(commandManager)
    local familyManager = commandManager.familyManager
    local graduatedChildren = {}
    local deadChildren = {}

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isGraduated() then
            graduatedChildren[#graduatedChildren + 1] = child:getName()
        elseif child:isDead() then
            deadChildren[#deadChildren + 1] = child:getName()
        end
    end

    commandManager:execute(FinishGame, graduatedChildren, deadChildren)
end

return CheckForGameEnd