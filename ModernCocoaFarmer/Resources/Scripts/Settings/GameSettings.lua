---------------------------------------------------------------------------------
GameSettings.GAME_SETTINGS_FILE_PATH = path.combine("Data", "Settings", "GameSettings.asset")

---------------------------------------------------------------------------------
function GameSettings.loadFromDefaultOrCreate()
    return GameSettings.load(GameSettings.GAME_SETTINGS_FILE_PATH) or GameSettings.create("GameSettings")
end

---------------------------------------------------------------------------------
function GameSettings:saveToDefault()
    self:save(GameSettings.GAME_SETTINGS_FILE_PATH)
end

---------------------------------------------------------------------------------
function GameSettings:synchronizeAudioSettings()
    self:setMasterVolume(Audio.getMasterVolume())
    self:setMusicVolume(Audio.getMusicVolume())
    self:setSFXVolume(Audio.getSFXVolume())
end