---------------------------------------------------------------------------------
local ModalDialogBase = {}

---------------------------------------------------------------------------------
function ModalDialogBase:new(rootGameObject)
    self.dialogRoot = rootGameObject
end

---------------------------------------------------------------------------------
function ModalDialogBase:hide()
    self._modalDialogManager:hideDialog(self)
end

---------------------------------------------------------------------------------
function ModalDialogBase:onShow()
end

---------------------------------------------------------------------------------
function ModalDialogBase:onHide()
end

return ModalDialogBase