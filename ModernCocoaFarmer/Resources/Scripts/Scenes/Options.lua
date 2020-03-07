require 'Settings.GameSettings'

---------------------------------------------------------------------------------
local OptionsScene = 
{
    OPTIONS_SCREEN_PATH = path.combine("Scenes", "Options.scene"),
    OPTIONS_SCREEN_ROOT_NAME = "OptionsScene",
    MASTER_VOLUME_SLIDER_NAME = "MasterVolumeSlider",
    MASTER_VOLUME_VALUE_NAME = "MasterVolumeValueText",
    MUSIC_VOLUME_SLIDER_NAME = "MusicVolumeSlider",
    MUSIC_VOLUME_VALUE_NAME = "MusicVolumeValueText",
    SFX_VOLUME_SLIDER_NAME = "SFXVolumeSlider",
    SFX_VOLUME_VALUE_NAME = "SFXVolumeValueText",
    CLOSE_BUTTON_NAME = "CloseButton",
}

---------------------------------------------------------------------------------
local function setValueText(gameObject, value)
    gameObject:findComponent("TextRenderer"):setText(tostring(value))
end

---------------------------------------------------------------------------------
local function masterVolumeSliderValueChanged(caller, newValue)
    Audio.setMasterVolume(newValue)

    local masterVolumeValueText = caller:findChild(OptionsScene.MASTER_VOLUME_VALUE_NAME)
    setValueText(masterVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function musicVolumeSliderValueChanged(caller, newValue)
    Audio.setMusicVolume(newValue)

    local musicVolumeValueText = caller:findChild(OptionsScene.MUSIC_VOLUME_VALUE_NAME)
    setValueText(musicVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function sfxVolumeSliderValueChanged(caller, newValue)
    Audio.setSFXVolume(newValue)

    local sfxVolumeValueText = caller:findChild(OptionsScene.SFX_VOLUME_VALUE_NAME)
    setValueText(sfxVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function saveAndTransitionToMainMenu(caller)
    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeAudioSettings()
    gameSettings:saveToDefault()

    GameObject.find(OptionsScene.OPTIONS_SCREEN_ROOT_NAME):destroy()

    local MainMenuScene = require 'Scenes.MainMenu'
    MainMenuScene.show()
end

---------------------------------------------------------------------------------
function OptionsScene.show()
    Scene.load(OptionsScene.OPTIONS_SCREEN_PATH)

    local masterVolumeSlider = GameObject.find(OptionsScene.MASTER_VOLUME_SLIDER_NAME)
    masterVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMasterVolume())
    masterVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(masterVolumeSliderValueChanged)
    setValueText(masterVolumeSlider:findChild(OptionsScene.MASTER_VOLUME_VALUE_NAME), Audio.getMasterVolume())

    local musicVolumeSlider = GameObject.find(OptionsScene.MUSIC_VOLUME_SLIDER_NAME)
    musicVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMusicVolume())
    musicVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(musicVolumeSliderValueChanged)
    setValueText(musicVolumeSlider:findChild(OptionsScene.MUSIC_VOLUME_VALUE_NAME), Audio.getMusicVolume())

    local sfxVolumeSlider = GameObject.find(OptionsScene.SFX_VOLUME_SLIDER_NAME)
    sfxVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getSFXVolume())
    sfxVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(sfxVolumeSliderValueChanged)
    setValueText(sfxVolumeSlider:findChild(OptionsScene.SFX_VOLUME_VALUE_NAME), Audio.getSFXVolume())

    local closeButton = GameObject.find(OptionsScene.CLOSE_BUTTON_NAME)
    closeButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(saveAndTransitionToMainMenu)
end

return OptionsScene
