local ShowModalDialog = {}

---------------------------------------------------------------------------------
function ShowModalDialog:new(dialogType, ...)
    self._dialogType = dialogType
    self._args = table.pack(...)
end

---------------------------------------------------------------------------------
function ShowModalDialog:execute(state)
    log("Showing Dialog " .. self._dialogType.__name)
    state.modalDialogManager:showDialog(self._dialogType, table.unpack(self._args))
end

return ShowModalDialog