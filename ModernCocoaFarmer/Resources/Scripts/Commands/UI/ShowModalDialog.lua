local ShowModalDialog = {}

---------------------------------------------------------------------------------
function ShowModalDialog:new(dialogType, ...)
    self._dialogType = dialogType
    self._args = table.pack(...)
end

---------------------------------------------------------------------------------
function ShowModalDialog:execute(commandManager)
    commandManager.modalDialogManager:showDialog(self._dialogType, commandManager, table.unpack(self._args))
end

return ShowModalDialog