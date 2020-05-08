local Finish = {}

---------------------------------------------------------------------------------
function Finish:new(graduatedChildren, deadChildren)
    self._graduatedChildren = graduatedChildren
    self._deadChildren = deadChildren
end

---------------------------------------------------------------------------------
function Finish:execute(commandManager)
    local GameplayScene = require 'Scenes.Gameplay'
    local FinishScene = require 'Scenes.Finish'

    GameplayScene.hide()
    FinishScene.show(self._graduatedChildren, self._deadChildren)
end

return Finish