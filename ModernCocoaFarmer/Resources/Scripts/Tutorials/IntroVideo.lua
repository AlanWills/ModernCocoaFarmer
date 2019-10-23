local tuts = require "Tutorials.Tutorials"

local iv = {}

---------------------------------------------------------------------------------
iv.INTRO_VIDEO_PATH = path.combine(Resources.getResourcesDirectory(), "Videos", "IntroMovie.mp4")

---------------------------------------------------------------------------------
function iv.showIntroVideoIfNecessary(videoCompleteCallback)
    if not tuts.isIntroVideoShown() then
        tuts.setIntroVideoAsShown()

        local videoSettings = { }

        videoSettings["AutoExit"] = true
        videoSettings["Volume"] = Audio.getMasterVolume()
        videoSettings["OnVideoComplete"] = videoCompleteCallback

        Video.play(iv.INTRO_VIDEO_PATH, videoSettings)
    else
        videoCompleteCallback()
    end
end

return iv