local Class = require 'OOP.Class'
local Tutorials = require "Tutorials.Tutorials"

---------------------------------------------------------------------------------
local ShowIntroVideo =
{
    INTRO_VIDEO_PATH = path.combine(Resources.getResourcesDirectory(), "Videos", "IntroMovie.mp4"),
}

---------------------------------------------------------------------------------
function ShowIntroVideo:new(onVideoComplete, forceShow)
    self._onVideoComplete = onVideoComplete
    self._forceShow = forceShow or false
end

---------------------------------------------------------------------------------
function ShowIntroVideo:execute()
    local isIntroVideoShown = Tutorials.isIntroVideoShown()

    if self._forceShow or not isIntroVideoShown then
        log("Playing intro video: force = " .. tostring(self._forceShow) .. " is_shown = " .. tostring(isIntroVideoShown))

        Tutorials.setIntroVideoAsShown()

        local videoSettings = { }
        videoSettings["AutoExit"] = true
        videoSettings["Volume"] = 1
        videoSettings["OnVideoComplete"] = self._onVideoComplete

        Video.play(ShowIntroVideo.INTRO_VIDEO_PATH, videoSettings)
    else
        log("Skipping intro video: force = " .. tostring(self._forceShow) .. " is_shown = " .. tostring(isIntroVideoShown))
        self._onVideoComplete()
    end
end

return ShowIntroVideo