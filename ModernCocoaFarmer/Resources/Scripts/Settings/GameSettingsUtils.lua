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
function GameSettings:synchronizeSettingsFromGame()
    self:setResolution(Viewport.getResolution())
    self:setMasterVolume(Audio.getMasterVolume())
    self:setMusicVolume(Audio.getMusicVolume())
    self:setSFXVolume(Audio.getSFXVolume())
end

---------------------------------------------------------------------------------
function GameSettings:synchronizeSettingsToGame()
    Viewport.setResolution(self:getResolution())
    Audio.setMasterVolume(self:getMasterVolume())
    Audio.setMusicVolume(self:getMusicVolume())
    Audio.setSFXVolume(self:getSFXVolume())
end