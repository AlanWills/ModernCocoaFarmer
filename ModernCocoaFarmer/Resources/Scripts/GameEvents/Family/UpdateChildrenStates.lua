local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local UpdateChildrenStatesCommand = require 'Commands.Family.UpdateChildrenStates'
local Finish = require 'Commands.State.Finish'

local UpdateChildrenStates = {}

---------------------------------------------------------------------------------
UpdateChildrenStates.NAME = "UpdateChildrenStates"
UpdateChildrenStates.PERIOD = GameEventPeriod.EVERY_DAY

---------------------------------------------------------------------------------
function UpdateChildrenStates.trigger(commandManager)
    commandManager:execute(UpdateChildrenStatesCommand)

    local familyManager = commandManager.familyManager
    local graduatedChildren = {}
    local deadChildren = {}

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isActivated() or child:isNotBorn() then
            -- Game is not over
            return
        elseif child:isGraduated() then
            graduatedChildren[#graduatedChildren + 1] = child:getName()
        elseif child:isDead() then
            deadChildren[#deadChildren + 1] = child:getName()
        end
    end

    commandManager:execute(Finish, graduatedChildren, deadChildren)
end

return UpdateChildrenStates