local HideModalDialog = require 'Commands.UI.HideModalDialog'

---------------------------------------------------------------------------------
local ModalDialogBase = {}

---------------------------------------------------------------------------------
function ModalDialogBase:new(commandManager, rootGameObject)
    self._commandManager = commandManager
    self.dialogRoot = rootGameObject
    self._keyPressedHandle = Keyboard.subscribeOnKeyPressedCallback(ModalDialogBase.hideCallback, self)
end

---------------------------------------------------------------------------------
function ModalDialogBase.hideCallback(key, self)
    if key == Key.Escape then
        self:hide()
    end
end

---------------------------------------------------------------------------------
function ModalDialogBase:hide()
    Keyboard.unsubscribeOnKeyPressedCallback(self._keyPressedHandle)
    
    self._keyPressedHandle = 0
    self._commandManager:execute(HideModalDialog, self)
end

return ModalDialogBase