---------------------------------------------------------------------------------
GameSettings.GAME_SETTINGS_FILE_PATH = path.combine("Data", "Settings", "GameSettings.asset")

---------------------------------------------------------------------------------
function GameSettings.loadFromDefaultOrCreate()
    local load = GameSettings.load(GameSettings.GAME_SETTINGS_FILE_PATH)
    if load ~= nil then
        return load
    end
    
    return GameSettings.create("GameSettings")
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