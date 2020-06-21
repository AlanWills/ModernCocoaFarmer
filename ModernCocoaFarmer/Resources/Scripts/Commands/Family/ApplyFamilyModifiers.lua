local ApplyFamilyModifiers = {}

---------------------------------------------------------------------------------
function ApplyFamilyModifiers:execute(commandManager)
    log("Applying family modifiers")
    commandManager.familyManager:applyDailyModifiers()
end

return ApplyFamilyModifiers