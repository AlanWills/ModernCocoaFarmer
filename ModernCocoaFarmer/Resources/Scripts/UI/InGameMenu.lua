local InGameMenu = {}

---------------------------------------------------------------------------------
InGameMenu.IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "InGameMenu.prefab")
InGameMenu.CLOSE_BUTTON_NAME = "CloseInGameMenuButton"
InGameMenu.TOGGLE_AUDIO_BUTTON_NAME = "ToggleAudioButton"
InGameMenu.RESUME_GAME_BUTTON_NAME = "ResumeGameButton"
InGameMenu.RESTART_GAME_BUTTON_NAME = "RestartGameButton"
InGameMenu.TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton"
InGameMenu.QUIT_GAME_BUTTON_NAME = "QuitGameButton"
InGameMenu.AUDIO_MUTED_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioMuted.png")
InGameMenu.AUDIO_PLAYING_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioPlaying.png")

----------------------------------------------------------------------------------------
local function close(eventArgs, caller)
    caller:getParent():die()
end

----------------------------------------------------------------------------------------
local function toggleAudio(eventArgs, caller)
    local masterVolume = Audio.getMasterVolume()

    if masterVolume > 0 then
        caller:findComponent("SpriteRenderer"):setTexture(InGameMenu.AUDIO_MUTED_TEXTURE_PATH)
        InGameMenu.oldMasterVolume = masterVolume
        Audio.setMasterVolume(0)
    else
        caller:findComponent("SpriteRenderer"):setTexture(InGameMenu.AUDIO_PLAYING_TEXTURE_PATH)
        Audio.setMasterVolume(InGameMenu.oldMasterVolume)
    end
end

---------------------------------------------------------------------------------
local function resumeGame(eventArgs, caller)
    close(eventArgs, caller)
end

---------------------------------------------------------------------------------
local function restartGame(eventArgs, caller)
    caller:getScreen():die()
end

---------------------------------------------------------------------------------
local function toMainMenu(eventArgs, caller)
    caller:getScreen():die()
end

---------------------------------------------------------------------------------
local function quitGame(eventArgs, caller)
    exit()
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
    menuInstance:setupChildLeftClickCallback(InGameMenu.TOGGLE_AUDIO_BUTTON_NAME, toggleAudio)
    menuInstance:setupChildLeftClickCallback(InGameMenu.RESUME_GAME_BUTTON_NAME, resumeGame)
    menuInstance:setupChildLeftClickCallback(InGameMenu.RESTART_GAME_BUTTON_NAME, restartGame)
    menuInstance:setupChildLeftClickCallback(InGameMenu.TO_MAIN_MENU_BUTTON_NAME, toMainMenu)
    menuInstance:setupChildLeftClickCallback(InGameMenu.QUIT_GAME_BUTTON_NAME, quitGame)
end

return InGameMenu