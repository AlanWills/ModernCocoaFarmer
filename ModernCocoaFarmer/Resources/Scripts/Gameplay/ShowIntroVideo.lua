local videoSettings = { }
videoSettings["AutoExit"] = true
videoSettings["OnVideoComplete"] = function()
    local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "MainMenu.screen")
    Screen.load(screenPath)
end

local videoPath = path.combine(Resources.getResourcesDirectory(), "Videos", "IntroMovie.mp4")
Video.play(videoPath, videoSettings)