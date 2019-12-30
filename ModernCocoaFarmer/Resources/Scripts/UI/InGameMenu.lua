require 'Settings.GameSettings'

local InGameMenu = {}

---------------------------------------------------------------------------------
InGameMenu.IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "InGameMenu.prefab")
InGameMenu.TOGGLE_AUDIO_BUTTON_NAME = "ToggleAudioButton"
InGameMenu.RESUME_GAME_BUTTON_NAME = "ResumeGameButton"
InGameMenu.RESTART_GAME_BUTTON_NAME = "RestartGameButton"
InGameMenu.TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton"
InGameMenu.QUIT_GAME_BUTTON_NAME = "QuitGameButton"
InGameMenu.AUDIO_MUTED_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioMuted.png")
InGameMenu.AUDIO_PLAYING_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioPlaying.png")
InGameMenu.oldMasterVolume = 1

----------------------------------------------------------------------------------------
local function close(eventArgs, caller)
    caller:getParent():die()
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
local function toggleAudio(eventArgs, caller)
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
local function resumeGame(eventArgs, caller)
    close(eventArgs, caller)
end

---------------------------------------------------------------------------------
local function restartGame(eventArgs, caller)
    caller:getScreen():die()
    
    local GameplayScreen = require 'Screens.GameplayScreen'
    GameplayScreen.show();
end

---------------------------------------------------------------------------------
local function toMainMenu(eventArgs, caller)
    caller:getScreen():die()

    local MainMenuScreen = require 'Screens.MainMenuScreen'
    MainMenuScreen.show()
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

    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.TOGGLE_AUDIO_BUTTON_NAME, toggleAudio)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.RESUME_GAME_BUTTON_NAME, resumeGame)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.RESTART_GAME_BUTTON_NAME, restartGame)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.TO_MAIN_MENU_BUTTON_NAME, toMainMenu)
    menuInstance:setupChildLeftButtonUpCallback(InGameMenu.QUIT_GAME_BUTTON_NAME, quitGame)

    setToggleAudioButtonTexture(menuInstance:findChildGameObject(InGameMenu.TOGGLE_AUDIO_BUTTON_NAME), Audio.getMasterVolume())
end

return InGameMenu