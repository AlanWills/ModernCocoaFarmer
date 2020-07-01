require 'Settings.GameSettingsUtils'

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
    RESOLUTION_NAME = "Resolution",
    RESOLUTION_TEXT_NAME = "ResolutionText",
    PREVIOUS_RESOLUTION_BUTTON_NAME = "PreviousResolutionButton",
    NEXT_RESOLUTION_BUTTON_NAME = "NextResolutionButton",
    APPLY_BUTTON_NAME = "ApplyButton",
    CLOSE_BUTTON_NAME = "CloseButton",
    RESOLUTIONS = 
    {
        vec2.new(1920, 1080),
        vec2.new(1280, 720),
    }
}

---------------------------------------------------------------------------------
local function setValueText(gameObject, value)
    gameObject:findComponent("TextRenderer"):setText(string.format("%d", math.round(value * 100)))
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
local function formatResolutionText(resolution)
    return string.format("%d x %d", resolution.x, resolution.y)
end

---------------------------------------------------------------------------------
local function setResolution(resolutionIndex)
    Options._currentResolutionIndex = resolutionIndex

    local resolution = Options.RESOLUTIONS[Options._currentResolutionIndex]
    Options._resolutionText:setText(formatResolutionText(resolution))
    Viewport.setResolution(resolution)
end

---------------------------------------------------------------------------------
local function previousResolution(caller)
    if Options._currentResolutionIndex == 1 then
        setResolution(#Options.RESOLUTIONS)
    else
        setResolution(Options._currentResolutionIndex - 1)
    end
end

---------------------------------------------------------------------------------
local function nextResolution(caller)
    if Options._currentResolutionIndex == #Options.RESOLUTIONS then
        setResolution(1)
    else
        setResolution(Options._currentResolutionIndex + 1)
    end
end

---------------------------------------------------------------------------------
local function apply(caller)
    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeSettingsFromGame()
    gameSettings:saveToDefault()
    gameSettings:destroy()
end

---------------------------------------------------------------------------------
local function close(caller)
    local gameSettings = GameSettings.loadFromDefaultOrCreate()
    gameSettings:synchronizeSettingsToGame()
    gameSettings:destroy()
    
    local Options = require 'Scenes.Options'
    Options.hide()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
local function findResolutionIndex(resolution)
    for i, res in ipairs(Options.RESOLUTIONS) do
        if res == resolution then
            return i
        end
    end

    return 1
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
    
    local resolution = Viewport.getResolution()
    local resolutionGameObject = GameObject.find(Options.RESOLUTION_NAME)
    local resolutionText = resolutionGameObject:findChild(Options.RESOLUTION_TEXT_NAME):findComponent("TextRenderer")
    resolutionText:setText(formatResolutionText(resolution))
    
    Options._resolutionText = resolutionText
    Options._currentResolutionIndex = findResolutionIndex(resolution)

    local previousResolutionButton = GameObject.find(Options.PREVIOUS_RESOLUTION_BUTTON_NAME)
    previousResolutionButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(previousResolution)
    
    local nextResolutionButton = GameObject.find(Options.NEXT_RESOLUTION_BUTTON_NAME)
    nextResolutionButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(nextResolution)

    local applyButton = GameObject.find(Options.APPLY_BUTTON_NAME)
    applyButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(apply)

    local closeButton = GameObject.find(Options.CLOSE_BUTTON_NAME)
    closeButton:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(close)
end

---------------------------------------------------------------------------------
function Options.hide()
    GameObject.find(Options.OPTIONS_ROOT_NAME):destroy()

    Options._resolutionText = nil
end

return Options
