local HideModalDialog = require 'Commands.UI.HideModalDialog'

---------------------------------------------------------------------------------
local ModalDialogBase = {}

---------------------------------------------------------------------------------
function ModalDialogBase:new(commandManager, rootGameObject)
    self._commandManager = commandManager
    self.dialogRoot = rootGameObject
end

---------------------------------------------------------------------------------
function ModalDialogBase:hide()
    self._commandManager:execute(HideModalDialog, self)
end

return ModalDialogBase