local Class = require 'OOP.Class'
local ModalDialogBase = require 'UI.Dialogs.ModalDialogBase'

----------------------------------------------------------------------------------------
local NotificationDialog = Class.inheritsFrom(ModalDialogBase)

NotificationDialog.NOTIFICATION_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationDialog.prefab")
NotificationDialog.NOTIFICATION_TITLE_NAME = "NotificationDialogTitle"
NotificationDialog.NOTIFICATION_DESCRIPTION_NAME = "NotificationDialogDescription"
NotificationDialog.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME = "CloseNotificationDialogButton"

---------------------------------------------------------------------------------
local function closeDialog(caller, self)
    self:hide()
end

---------------------------------------------------------------------------------
function NotificationDialog:new(commandManager, notificationTitle, notificationDescription)
    local dialogPrefab = Resources.loadPrefab(self.NOTIFICATION_DIALOG_PREFAB_PATH)
    self._gameObject = dialogPrefab:instantiate()

    ModalDialogBase.new(self, commandManager, self._gameObject)

    local notificationTitleGameObject = self._gameObject:findChild(self.NOTIFICATION_TITLE_NAME)
    
    notificationTitleGameObject:findComponent("TextRenderer"):setText(notificationTitle)
    self._gameObject:findChild(self.NOTIFICATION_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(notificationDescription)
    self._gameObject:setupChildLeftButtonUpCallback(self.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME, closeDialog, self)
end

return NotificationDialog