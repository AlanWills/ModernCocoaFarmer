local InGameMenu = {}

---------------------------------------------------------------------------------
InGameMenu.IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "InGameMenu.prefab")

----------------------------------------------------------------------------------------
function InGameMenu.load()
    return Resources.loadPrefab(InGameMenu.IN_GAME_MENU_PREFAB_PATH)
end

---------------------------------------------------------------------------------
function InGameMenu.show(screen, familyManager)
    local menuPrefab = InGameMenu.load()
    local menuInstance = menuPrefab:instantiate(screen)
end

return InGameMenu