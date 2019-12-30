local EventDialog =
{
    EVENT_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Events", "EventDialog.prefab")
    EVENT_TITLE_NAME = "EventDialogTitle",
    EVENT_DESCRIPTION_NAME = "EventDialogDescription"
    CLOSE_EVENT_DIALOG_BUTTON_NAME = "CloseEventDialogButton"
}

---------------------------------------------------------------------------------
local function closeDialog(eventArgs, caller)
    caller:getParent():die()
end

---------------------------------------------------------------------------------
function EventDialog:new(screen, gameEvent)
    local dialogPrefab = Resources.loadPrefab(self.EVENT_DIALOG_PREFAB_PATH)
    local dialogInstance = dialogPrefab:instantiate(screen)

    dialogInstance:findChildGameObject(self.EVENT_TITLE_NAME):findComponent("TextRenderer"):setText(gameEvent:getName())
    dialogInstance:findChildGameObject(self.EVENT_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(gameEvent:getDescription())
    dialogInstance:setupChildLeftButtonUpCallback(self.CLOSE_EVENT_DIALOG_BUTTON_NAME, closeDialog)
end