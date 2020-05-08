local ApplyFamilyModifiers = {}

---------------------------------------------------------------------------------
function ApplyFamilyModifiers:execute(commandManager)
    commandManager.familyManager:applyDailyModifiers()
end

return ApplyFamilyModifiers