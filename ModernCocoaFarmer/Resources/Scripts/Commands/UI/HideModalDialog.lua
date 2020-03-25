local HideModalDialog = {}

---------------------------------------------------------------------------------
function HideModalDialog:new(dialog)
    self._dialog = dialog
end

---------------------------------------------------------------------------------
function HideModalDialog:execute(state)
    log("Hiding Dialog " .. self._dialog.__name)
    state.modalDialogManager:hideDialog(self._dialog)
end

return HideModalDialog