local NotificationDialog =
{
    NOTIFICATION_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationDialog.prefab"),
    NOTIFICATION_TITLE_NAME = "NotificationDialogTitle",
    NOTIFICATION_DESCRIPTION_NAME = "NotificationDialogDescription",
    CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME = "CloseNotificationDialogButton"
}

---------------------------------------------------------------------------------
local function closeDialog(caller)
    caller:getParent():destroy()
end

---------------------------------------------------------------------------------
function NotificationDialog:new(notificationTitle, notificationDescription)
    local dialogPrefab = Resources.loadPrefab(self.NOTIFICATION_DIALOG_PREFAB_PATH)
    local dialogInstance = dialogPrefab:instantiate()
    local notificationTitleGameObject = dialogInstance:findChild(self.NOTIFICATION_TITLE_NAME)
    
    notificationTitleGameObject:findComponent("TextRenderer"):setText(notificationTitle)
    dialogInstance:findChild(self.NOTIFICATION_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(notificationDescription)
    dialogInstance:setupChildLeftButtonUpCallback(self.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME, closeDialog)
end

return NotificationDialog