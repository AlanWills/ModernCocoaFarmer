local GameEventDialog =
{
    GAME_EVENT_DIALOG_PREFAB_PATH = path.combine("Prefabs", "UI", "Events", "GameEventDialog.prefab"),
    GAME_EVENT_TITLE_NAME = "GameEventDialogTitle",
    GAME_EVENT_DESCRIPTION_NAME = "GameEventDialogDescription",
    CLOSE_GAME_EVENT_DIALOG_BUTTON_NAME = "CloseGameEventDialogButton"
}

---------------------------------------------------------------------------------
local function closeDialog(eventArgs, caller)
    caller:getParent():die()
end

---------------------------------------------------------------------------------
function GameEventDialog:new(screen, gameEvent)
    local dialogPrefab = Resources.loadPrefab(self.GAME_EVENT_DIALOG_PREFAB_PATH)
    local dialogInstance = dialogPrefab:instantiate(screen)
    local eventTitle = dialogInstance:findChildGameObject(self.GAME_EVENT_TITLE_NAME)
    local eventName = gameEvent:getName()
    
    eventTitle:findComponent("TextRenderer"):setText(eventName)
    dialogInstance:findChildGameObject(self.GAME_EVENT_DESCRIPTION_NAME):findComponent("TextRenderer"):setText(gameEvent:getDescription())
    dialogInstance:setupChildLeftButtonUpCallback(self.CLOSE_GAME_EVENT_DIALOG_BUTTON_NAME, closeDialog)
end

return GameEventDialog