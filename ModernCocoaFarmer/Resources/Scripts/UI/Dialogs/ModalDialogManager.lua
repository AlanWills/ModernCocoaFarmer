local Class = require 'OOP.Class'
local Queue = require 'Containers.Queue'

---------------------------------------------------------------------------------
local ModalDialogManager =
{
    MODAL_DIALOG_MANAGER_NAME = "ModalDialogManager",
    MODAL_DIALOG_BASE_PREFAB_PATH = path.combine("Prefabs", "UI", "Dialogs", "ModalDialogBase.prefab"),
    INPUT_BLOCKER_NAME = "InputBlocker",
    DIALOG_ROOT_NAME = "DialogRoot",
}

---------------------------------------------------------------------------------
function ModalDialogManager:new(rootGameObject)
    self._rootGameObject = rootGameObject
    self._dialogQueue = Class.new(Queue)
end

---------------------------------------------------------------------------------
function ModalDialogManager:showDialog(dialogType, ...)
    local dialog = Class.new(dialogType, ...)
    local modalDialogBasePrefab = Resources.loadPrefab(self.MODAL_DIALOG_BASE_PREFAB_PATH)
    local modalDialogBase = modalDialogBasePrefab:instantiate()

    -- Set up the dialog
    local inputBlocker = modalDialogBase:findChild(self.INPUT_BLOCKER_NAME)
    local dialogRoot = modalDialogBase:findChild(self.DIALOG_ROOT_NAME)
    dialog.dialogRoot:setParent(dialogRoot);
    dialog._modalDialogManager = self

    inputBlocker:setActive(true)
    modalDialogBase:setParent(self._rootGameObject)

    dialog:onShow()
end

---------------------------------------------------------------------------------
function ModalDialogManager:hideDialog(dialog)
    dialog:onHide()

    -- dialogRoot parent = DIALOG_ROOT_NAME
    -- DIALOG_ROOT_NAME parent = MODAL_DIALOG_BASE
    dialog.dialogRoot:getParent():getParent():destroy()
end

return ModalDialogManager