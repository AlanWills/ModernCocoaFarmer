local OptionsScreen = {}

---------------------------------------------------------------------------------
OptionsScreen.OPTIONS_SCREEN_PATH = path.combine("Screens", "Options.screen")
OptionsScreen.GAME_SETTINGS_FILE_PATH = path.combine("Data", "Settings", "GameSettings.asset")
OptionsScreen.MASTER_VOLUME_SLIDER_NAME = "MasterVolumeSlider"
OptionsScreen.MASTER_VOLUME_VALUE_NAME = "MasterVolumeValueText"
OptionsScreen.MUSIC_VOLUME_SLIDER_NAME = "MusicVolumeSlider"
OptionsScreen.MUSIC_VOLUME_VALUE_NAME = "MusicVolumeValueText"
OptionsScreen.SFX_VOLUME_SLIDER_NAME = "SFXVolumeSlider"
OptionsScreen.SFX_VOLUME_VALUE_NAME = "SFXVolumeValueText"
OptionsScreen.CLOSE_BUTTON_NAME = "CloseButton"

---------------------------------------------------------------------------------
local function setValueText(gameObject, value)
    gameObject:findComponent("TextRenderer"):setText(tostring(value))
end

---------------------------------------------------------------------------------
local function masterVolumeSliderValueChanged(eventArgs, caller, newValue)
    Audio.setMasterVolume(newValue)

    local masterVolumeValueText = caller:findChildGameObject(OptionsScreen.MASTER_VOLUME_VALUE_NAME)
    setValueText(masterVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function musicVolumeSliderValueChanged(eventArgs, caller, newValue)
    Audio.setMusicVolume(newValue)

    local musicVolumeValueText = caller:findChildGameObject(OptionsScreen.MUSIC_VOLUME_VALUE_NAME)
    setValueText(musicVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function sfxVolumeSliderValueChanged(eventArgs, caller, newValue)
    Audio.setSFXVolume(newValue)

    local sfxVolumeValueText = caller:findChildGameObject(OptionsScreen.SFX_VOLUME_VALUE_NAME)
    setValueText(sfxVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function saveAndTransitionToMainMenu(eventArgs, caller)
    local gameSettings = GameSettings.load(OptionsScreen.GAME_SETTINGS_FILE_PATH) or GameSettings.create("GameSettings")
    
    gameSettings:setMasterVolume(Audio.getMasterVolume())
    gameSettings:setMusicVolume(Audio.getMusicVolume())
    gameSettings:setSFXVolume(Audio.getSFXVolume())
    gameSettings:save(OptionsScreen.GAME_SETTINGS_FILE_PATH)

    caller:getScreen():die()

    local MainMenuScreen = require 'Screens.MainMenuScreen'
    MainMenuScreen.show()
end

---------------------------------------------------------------------------------
function OptionsScreen.show()
    local optionsScreen = Screen.load(OptionsScreen.OPTIONS_SCREEN_PATH)

    local masterVolumeSlider = optionsScreen:findGameObject(OptionsScreen.MASTER_VOLUME_SLIDER_NAME)
    masterVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMasterVolume())
    masterVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(masterVolumeSliderValueChanged)
    setValueText(masterVolumeSlider:findChildGameObject(OptionsScreen.MASTER_VOLUME_VALUE_NAME), Audio.getMasterVolume())

    local musicVolumeSlider = optionsScreen:findGameObject(OptionsScreen.MUSIC_VOLUME_SLIDER_NAME)
    musicVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMusicVolume())
    musicVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(musicVolumeSliderValueChanged)
    setValueText(musicVolumeSlider:findChildGameObject(OptionsScreen.MUSIC_VOLUME_VALUE_NAME), Audio.getMusicVolume())

    local sfxVolumeSlider = optionsScreen:findGameObject(OptionsScreen.SFX_VOLUME_SLIDER_NAME)
    sfxVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getSFXVolume())
    sfxVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(sfxVolumeSliderValueChanged)
    setValueText(sfxVolumeSlider:findChildGameObject(OptionsScreen.SFX_VOLUME_VALUE_NAME), Audio.getSFXVolume())

    local closeButton = optionsScreen:findGameObject(OptionsScreen.CLOSE_BUTTON_NAME)
    closeButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(saveAndTransitionToMainMenu)
end

return OptionsScreen