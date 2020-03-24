local Class = require 'OOP.Class'

---------------------------------------------------------------------------------
local ModalDialogManager =
{
    MODAL_DIALOG_MANAGER_NAME = "ModalDialogManager",
    INPUT_BLOCKER_NAME = "InputBlocker",
    DIALOG_ROOT_NAME = "DialogRoot",
}

---------------------------------------------------------------------------------
function ModalDialogManager:new(rootGameObject)
    self._inputBlocker = rootGameObject:findChild(self.INPUT_BLOCKER_NAME)
    self._dialogRoot = rootGameObject:findChild(self.DIALOG_ROOT_NAME)
end

---------------------------------------------------------------------------------
function ModalDialogManager:queueDialog(dialog)
    self._inputBlocker:setActive(true)
    dialog:setParent(self._dialogRoot)
end

return ModalDialogManager