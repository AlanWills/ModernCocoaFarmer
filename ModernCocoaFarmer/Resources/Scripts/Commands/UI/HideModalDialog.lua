local HideModalDialog = {}

---------------------------------------------------------------------------------
function HideModalDialog:new(dialog)
    self._dialog = dialog
end

---------------------------------------------------------------------------------
function HideModalDialog:execute(commandManager)
    commandManager.modalDialogManager:hideDialog(self._dialog)
end

return HideModalDialog