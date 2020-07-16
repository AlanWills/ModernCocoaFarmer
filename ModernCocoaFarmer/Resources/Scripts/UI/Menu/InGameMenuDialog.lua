local Class = require 'OOP.Class'
local ModalDialogBase = require 'UI.Dialogs.ModalDialogBase'
local SaveGame = require 'Commands.State.SaveGame'
local LoadGame = require 'Commands.State.LoadGame'
local GameplayState = require 'State.GameplayState'

require 'Settings.GameSettingsUtils'

---------------------------------------------------------------------------------
local InGameMenuDialog = Class.inheritsFrom(ModalDialogBase)

InGameMenuDialog.IN_GAME_MENU_PREFAB_PATH = path.combine("Prefabs", "UI", "Menu", "InGameMenuDialog.prefab")
InGameMenuDialog.TOGGLE_AUDIO_BUTTON_NAME = "ToggleAudioButton"
InGameMenuDialog.RESUME_GAME_BUTTON_NAME = "ResumeGameButton"
InGameMenuDialog.SAVE_GAME_BUTTON_NAME = "SaveGameButton"
InGameMenuDialog.LOAD_GAME_BUTTON_NAME = "LoadGameButton"
InGameMenuDialog.TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton"
InGameMenuDialog.QUIT_GAME_BUTTON_NAME = "QuitGameButton"
InGameMenuDialog.AUDIO_MUTED_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioMuted.png")
InGameMenuDialog.AUDIO_PLAYING_TEXTURE_PATH = path.combine("Textures", "UI", "Settings", "AudioPlaying.png")
InGameMenuDialog.oldMasterVolume = 1

----------------------------------------------------------------------------------------
function InGameMenuDialog.close(caller, self)
    self:hide()
end

---------------------------------------------------------------------------------
function InGameMenuDialog.setToggleAudioButtonTexture(audioButton, volume)
    if volume > 0 then
        audioButton:findComponent("SpriteRenderer"):setTexture(InGameMenuDialog.AUDIO_PLAYING_TEXTURE_PATH)
    else
        audioButton:findComponent("SpriteRenderer"):setTexture(InGameMenuDialog.AUDIO_MUTED_TEXTURE_PATH)
    end
end

----------------------------------------------------------------------------------------
function InGameMenuDialog.toggleAudio(caller)
    local masterVolume = Audio.getMasterVolume()

    if masterVolume > 0 then
        InGameMenuDialog.oldMasterVolume = masterVolume
        masterVolume = 0
    else
        masterVolume = InGameMenuDialog.oldMasterVolume
    end

    Audio.setMasterVolume(masterVolume)
    InGameMenuDialog.setToggleAudioButtonTexture(caller, masterVolume)

    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeSettingsFromGame()
    gameSettings:saveToDefault()
end

---------------------------------------------------------------------------------
function InGameMenuDialog.saveGame(caller, self)
    InGameMenuDialog.close(caller, self)

    self._commandManager:execute(SaveGame)
end

---------------------------------------------------------------------------------
function InGameMenuDialog.loadGame(caller, self)
    InGameMenuDialog.close(caller, self)
    
    local Gameplay = require 'Scenes.Gameplay'
    Gameplay.hide()

    Class.new(LoadGame):execute()
end

---------------------------------------------------------------------------------
function InGameMenuDialog.toMainMenu(caller, self)
    InGameMenuDialog.close(caller, self)

    local Gameplay = require 'Scenes.Gameplay'
    Gameplay.hide()

    local MenuMusic = require 'Scenes.MenuMusic'
    MenuMusic.show()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
function InGameMenuDialog.quitGame(caller)
    exit()
end

----------------------------------------------------------------------------------------
function InGameMenuDialog.load()
    return Resources.loadPrefab(InGameMenuDialog.IN_GAME_MENU_PREFAB_PATH)
end

---------------------------------------------------------------------------------
function InGameMenuDialog:new(commandManager)
    local menuPrefab = InGameMenuDialog.load()
    self._gameObject = menuPrefab:instantiate()

    ModalDialogBase.new(self, commandManager, self._gameObject)

    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.TOGGLE_AUDIO_BUTTON_NAME, InGameMenuDialog.toggleAudio)
    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.RESUME_GAME_BUTTON_NAME, InGameMenuDialog.close, self)
    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.SAVE_GAME_BUTTON_NAME, InGameMenuDialog.saveGame, self)
    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.LOAD_GAME_BUTTON_NAME, InGameMenuDialog.loadGame, self)
    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.TO_MAIN_MENU_BUTTON_NAME, InGameMenuDialog.toMainMenu, self)
    self._gameObject:setupChildLeftButtonUpCallback(InGameMenuDialog.QUIT_GAME_BUTTON_NAME, InGameMenuDialog.quitGame)

    InGameMenuDialog.setToggleAudioButtonTexture(self._gameObject:findChild(InGameMenuDialog.TOGGLE_AUDIO_BUTTON_NAME), Audio.getMasterVolume())
    self:updateLoadGameButtonVisibility()
end

---------------------------------------------------------------------------------
function InGameMenuDialog:updateLoadGameButtonVisibility()
    local loadGameButton = self._gameObject:findChild(InGameMenuDialog.LOAD_GAME_BUTTON_NAME)
    loadGameButton:setActive(GameplayState.hasSave())
    self._gameObject:findComponent("StackPanel"):layout()
end

return InGameMenuDialog