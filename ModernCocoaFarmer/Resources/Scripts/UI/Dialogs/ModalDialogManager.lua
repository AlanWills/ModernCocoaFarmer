local Class = require 'OOP.Class'

---------------------------------------------------------------------------------
local ModalDialogManager =
{
    MODAL_DIALOG_BASE_PREFAB_PATH = path.combine("Prefabs", "UI", "Dialogs", "ModalDialogBase.prefab"),
    DIALOG_GRAVEYARD_NAME = "DialogGraveyard",
    INPUT_BLOCKER_NAME = "InputBlocker",
    DIALOG_ROOT_NAME = "DialogRoot",
}

---------------------------------------------------------------------------------
function ModalDialogManager:new(rootGameObject)
    self._rootGameObject = rootGameObject
    self._dialogGraveyard = rootGameObject:findChild(self.DIALOG_GRAVEYARD_NAME)
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
end

---------------------------------------------------------------------------------
function ModalDialogManager:hideDialog(dialog)
    -- This section is a workaround for a bug where managed components are still active and updated when
    -- active game objects are added to an inactive tree
    local modalDialogBase = dialog.dialogRoot:getParent():getParent()
    local inputBlocker = modalDialogBase:findChild(self.INPUT_BLOCKER_NAME):setActive(false)
    local dialogRoot = modalDialogBase:findChild(self.DIALOG_ROOT_NAME):setActive(false)
    
    -- Due to a bug in the engine, we cannot destroy parents from children
    -- Once this is resolved, uncomment this
    -- dialog.dialogRoot:getParent():getParent():destroy()

    -- For now we do this workaround, of reparenting and then destroying later
    dialog.dialogRoot:setParent(self._dialogGraveyard)
    dialog.dialogRoot:setActive(false)
end

---------------------------------------------------------------------------------
function ModalDialogManager:destroyDialogs()
    -- Clean up the dialog graveyard
    local childIndex = self._dialogGraveyard:getChildCount()

    while childIndex > 0 do
        childIndex = childIndex - 1
        self._dialogGraveyard:getChild(childIndex):destroy()
    end
end

return ModalDialogManager