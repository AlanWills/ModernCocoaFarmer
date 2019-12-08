local InGameMenu = {}

---------------------------------------------------------------------------------
InGameMenu.IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "InGameMenu.prefab")
InGameMenu.CLOSE_BUTTON_NAME = "CloseInGameMenuButton"

----------------------------------------------------------------------------------------
local function close(eventArgs, caller)
    caller:die()
end

----------------------------------------------------------------------------------------
function InGameMenu.load()
    return Resources.loadPrefab(InGameMenu.IN_GAME_MENU_PREFAB_PATH)
end

---------------------------------------------------------------------------------
function InGameMenu.show(screen, familyManager)
    local menuPrefab = InGameMenu.load()
    local menuInstance = menuPrefab:instantiate(screen)

    menuInstance:setupChildLeftClickCallback(InGameMenu.CLOSE_BUTTON_NAME, close)
end

return InGameMenu