local Class = require 'OOP.Class'
local ModalDialogBase = require 'UI.Dialogs.ModalDialogBase'

----------------------------------------------------------------------------------------
local NotificationDialog = Class.inheritsFrom(ModalDialogBase)

NotificationDialog.NOTIFICATION_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationDialog.prefab")
NotificationDialog.NOTIFICATION_TITLE_NAME = "NotificationDialogTitle"
NotificationDialog.NOTIFICATION_DESCRIPTION_NAME = "NotificationDialogDescription"
NotificationDialog.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME = "CloseNotificationDialogButton"
NotificationDialog.DEFAULT_SFX_PATH = path.combine("Audio", "SFX", "Notification.wav")

---------------------------------------------------------------------------------
function NotificationDialog.closeDialog(caller, self)
    self:hide()
end

---------------------------------------------------------------------------------
function NotificationDialog:new(commandManager, notificationTitle, notificationDescription, notificationSfx)
    local dialogPrefab = Resources.loadPrefab(self.NOTIFICATION_DIALOG_PREFAB_PATH)
    self._gameObject = dialogPrefab:instantiate()

    ModalDialogBase.new(self, commandManager, self._gameObject)

    self._gameObject:findChild(self.NOTIFICATION_TITLE_NAME):findComponent("TextRenderer"):setText(notificationTitle)
    self._gameObject:findChild(self.NOTIFICATION_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(notificationDescription)
    self._gameObject:setupChildLeftButtonUpCallback(self.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME, NotificationDialog.closeDialog, self)
    
    notificationSfx = notificationSfx or NotificationDialog.DEFAULT_SFX_PATH
    local notificationAudioSource = self._gameObject:findComponent("AudioSource")
    notificationAudioSource:setSound(notificationSfx)
    notificationAudioSource:play()
end

return NotificationDialog