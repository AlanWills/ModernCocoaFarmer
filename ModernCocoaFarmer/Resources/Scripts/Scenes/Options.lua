require 'Settings.GameSettings'

---------------------------------------------------------------------------------
local Options = 
{
    OPTIONS_SCENE_PATH = path.combine("Scenes", "Options.scene"),
    OPTIONS_ROOT_NAME = "OptionsScene",
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

    local masterVolumeValueText = caller:findChild(Options.MASTER_VOLUME_VALUE_NAME)
    setValueText(masterVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function musicVolumeSliderValueChanged(caller, newValue)
    Audio.setMusicVolume(newValue)

    local musicVolumeValueText = caller:findChild(Options.MUSIC_VOLUME_VALUE_NAME)
    setValueText(musicVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function sfxVolumeSliderValueChanged(caller, newValue)
    Audio.setSFXVolume(newValue)

    local sfxVolumeValueText = caller:findChild(Options.SFX_VOLUME_VALUE_NAME)
    setValueText(sfxVolumeValueText, newValue)
end

---------------------------------------------------------------------------------
local function saveAndTransitionToMainMenu(caller)
    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeAudioSettings()
    gameSettings:saveToDefault()

    local Options = require 'Scenes.Options'
    Options.hide()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
function Options.show()
    Scene.load(Options.OPTIONS_SCENE_PATH)

    local masterVolumeSlider = GameObject.find(Options.MASTER_VOLUME_SLIDER_NAME)
    masterVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMasterVolume())
    masterVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(masterVolumeSliderValueChanged)
    setValueText(masterVolumeSlider:findChild(Options.MASTER_VOLUME_VALUE_NAME), Audio.getMasterVolume())

    local musicVolumeSlider = GameObject.find(Options.MUSIC_VOLUME_SLIDER_NAME)
    musicVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getMusicVolume())
    musicVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(musicVolumeSliderValueChanged)
    setValueText(musicVolumeSlider:findChild(Options.MUSIC_VOLUME_VALUE_NAME), Audio.getMusicVolume())

    local sfxVolumeSlider = GameObject.find(Options.SFX_VOLUME_SLIDER_NAME)
    sfxVolumeSlider:findComponent("Slider"):setCurrentValue(Audio.getSFXVolume())
    sfxVolumeSlider:findComponent("Slider"):subscribeOnValueChangedCallback(sfxVolumeSliderValueChanged)
    setValueText(sfxVolumeSlider:findChild(Options.SFX_VOLUME_VALUE_NAME), Audio.getSFXVolume())

    local closeButton = GameObject.find(Options.CLOSE_BUTTON_NAME)
    closeButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(saveAndTransitionToMainMenu)
end

---------------------------------------------------------------------------------
function Options.hide()
    GameObject.find(Options.OPTIONS_ROOT_NAME):destroy()
end

return Options
