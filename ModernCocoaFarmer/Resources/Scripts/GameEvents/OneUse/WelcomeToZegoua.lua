local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local SendNotification = require 'Commands.Notifications.SendNotification'

local WelcomeToZegoua = {}

---------------------------------------------------------------------------------
WelcomeToZegoua.NAME = "WelcomeToZegoua"
WelcomeToZegoua.DAY_TO_TRIGGER = 1
WelcomeToZegoua.MONTH_TO_TRIGGER = 0
WelcomeToZegoua.YEAR_TO_TRIGGER = 0
WelcomeToZegoua.PERIOD = GameEventPeriod.EVERY_DAY
WelcomeToZegoua.ICON_PATH = path.combine("Textures", "Icons", "Events", "WelcomeToZegoua.png")

---------------------------------------------------------------------------------
function WelcomeToZegoua.canTrigger(commandManager)
    local timeManager = commandManager.timeManager

    return timeManager:getCurrentDay() == WelcomeToZegoua.DAY_TO_TRIGGER and
           timeManager:getCurrentMonth() == WelcomeToZegoua.MONTH_TO_TRIGGER and
           timeManager:getCurrentYear() == WelcomeToZegoua.YEAR_TO_TRIGGER
end

---------------------------------------------------------------------------------
function WelcomeToZegoua.trigger(commandManager)
    commandManager:execute(
        SendNotification,
        "Welcome To Zegoua!",
        "Click on the icons to find out about the locations",
        WelcomeToZegoua.ICON_PATH)
end

return WelcomeToZegoua