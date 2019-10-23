local tuts = {}

---------------------------------------------------------------------------------
tuts.DATA_STORE_PATH = path.combine("Data", "AppData", "TutorialDataStore.xml")
tuts.INTRO_VIDEO_SHOWN_KEY = "IntroVideoShown"

---------------------------------------------------------------------------------
function tuts.isIntroVideoShown()
    local dataStore = DataStore.loadOrCreate(tuts.DATA_STORE_PATH)
    return dataStore:getBool(tuts.INTRO_VIDEO_SHOWN_KEY, false)
end

---------------------------------------------------------------------------------
function tuts.setIntroVideoAsShown()
    local dataStore = DataStore.loadOrCreate(tuts.DATA_STORE_PATH)
    dataStore:setBool(tuts.INTRO_VIDEO_SHOWN_KEY, true)
    
    if not dataStore:save(tuts.DATA_STORE_PATH) then
        log("Failed to save tutorial data store")
        assertFail()
    end
end

return tuts