local NotificationDialog =
{
    NOTIFICATION_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationDialog.prefab"),
    NOTIFICATION_TITLE_NAME = "NotificationDialogTitle",
    NOTIFICATION_DESCRIPTION_NAME = "NotificationDialogDescription",
    CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME = "CloseNotificationDialogButton"
}

---------------------------------------------------------------------------------
local function closeDialog(eventArgs, caller)
    caller:getParent():die()
end

---------------------------------------------------------------------------------
function NotificationDialog:new(screen, notification)
    local dialogPrefab = Resources.loadPrefab(self.NOTIFICATION_DIALOG_PREFAB_PATH)
    local dialogInstance = dialogPrefab:instantiate(screen)
    local notificationTitle = dialogInstance:findChildGameObject(self.NOTIFICATION_TITLE_NAME)
    
    eventTitle:findComponent("TextRenderer"):setText(notification:getName())
    dialogInstance:findChildGameObject(self.NOTIFICATION_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(notification:getDescription())
    dialogInstance:setupChildLeftButtonUpCallback(self.CLOSE_NOTIFICATION_DIALOG_BUTTON_NAME, closeDialog)
end

return NotificationDialog