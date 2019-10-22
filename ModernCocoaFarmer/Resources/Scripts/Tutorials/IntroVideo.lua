local tuts = require "Tutorials.Tutorials"

local siv = {}

---------------------------------------------------------------------------------
local function loadMainMenu()
    local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "MainMenu.screen")
    Screen.load(screenPath)
end

---------------------------------------------------------------------------------
function siv.showIntroVideoIfNecessary()
    if not tuts.isIntroVideoShown() then
        tuts.setIntroVideoAsShown()

        local videoSettings = { }

        videoSettings["AutoExit"] = true
        videoSettings["Volume"] = Audio.getMasterVolume()
        videoSettings["OnVideoComplete"] = loadMainMenu

        local videoPath = path.combine(Resources.getResourcesDirectory(), "Videos", "IntroMovie.mp4")
        Video.play(videoPath, videoSettings)
    else
        loadMainMenu()
    end
end

return siv