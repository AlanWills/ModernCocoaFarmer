require 'Settings.GameSettings'

---------------------------------------------------------------------------------
local InGameMenu =
{
    IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "InGameMenu.prefab"),
    TOGGLE_AUDIO_BUTTON_NAME = "ToggleAudioButton",
    RESUME_GAME_BUTTON_NAME = "ResumeGameButton",
    RESTART_GAME_BUTTON_NAME = "RestartGameButton",
    TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton",
    QUIT_GAME_BUTTON_NAME = "QuitGameButton",
    AUDIO_MUTED_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioMuted.png"),
    AUDIO_PLAYING_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioPlaying.png"),
    oldMasterVolume = 1,
}

----------------------------------------------------------------------------------------
local function close(caller)
    caller:getParent():destroy()
end

---------------------------------------------------------------------------------
local function setToggleAudioButtonTexture(audioButton, volume)
    if volume > 0 then
        audioButton:findComponent("SpriteRenderer"):setTexture(InGameMenu.AUDIO_PLAYING_TEXTURE_PATH)
    else
        audioButton:findComponent("SpriteRenderer"):setTexture(InGameMenu.AUDIO_MUTED_TEXTURE_PATH)
    end
end

----------------------------------------------------------------------------------------
local function toggleAudio(caller)
    local masterVolume = Audio.getMasterVolume()

    if masterVolume > 0 then
        InGameMenu.oldMasterVolume = masterVolume
        masterVolume = 0
    else
        masterVolume = InGameMenu.oldMasterVolume
    end

    Audio.setMasterVolume(masterVolume)
    setToggleAudioButtonTexture(caller, masterVolume)

    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeAudioSettings()
    gameSettings:saveToDefault()
end

---------------------------------------------------------------------------------
local function resumeGame(caller)
    close(caller)
end

---------------------------------------------------------------------------------
local function restartGame(caller)
    close(caller)

    local Gameplay = require 'Scenes.Gameplay'
    Gameplay.hide()
    Gameplay.show()
end

---------------------------------------------------------------------------------
local function toMainMenu(caller)
    close(caller)

    local Gameplay = require 'Scenes.Gameplay'
    Gameplay.hide()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
local function quitGame(caller)
    exit()
end

----------------------------------------------------------------------------------------
function InGameMenu.load()
    return Resources.loadPrefab(InGameMenu.IN_GAME_MENU_PREFAB_PATH)
end

---------------------------------------------------------------------------------
function InGameMenu.show(familyManager)
    local menuPrefab = InGameMenu.load()
    local menuInstance = menuPrefab:instantiate()

    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.TOGGLE_AUDIO_BUTTON_NAME, toggleAudio)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.RESUME_GAME_BUTTON_NAME, resumeGame)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.RESTART_GAME_BUTTON_NAME, restartGame)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.TO_MAIN_MENU_BUTTON_NAME, toMainMenu)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.QUIT_GAME_BUTTON_NAME, quitGame)

    setToggleAudioButtonTexture(menuInstance:findChild(InGameMenu.TOGGLE_AUDIO_BUTTON_NAME), Audio.getMasterVolume())
end

return InGameMenu