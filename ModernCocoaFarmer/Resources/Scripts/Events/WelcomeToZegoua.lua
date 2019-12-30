local WelcomeToZegoua = 
{
    information = GameEvent.load(path.combine("Data", "Events", "WelcomeToZegoua.asset"))
}

---------------------------------------------------------------------------------
function WelcomeToZegoua:getTitle()
    return self.information:getTitle()
end

---------------------------------------------------------------------------------
function WelcomeToZegoua:getDescription()
    return self.information:getDescription()
end

return WelcomeToZegoua