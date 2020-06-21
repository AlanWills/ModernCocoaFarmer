local FinishGame = {}

---------------------------------------------------------------------------------
function FinishGame:new(graduatedChildren, deadChildren)
    self._graduatedChildren = graduatedChildren
    self._deadChildren = deadChildren
end

---------------------------------------------------------------------------------
function FinishGame:execute(commandManager)
    log("Finishing game")

    local GameplayScene = require 'Scenes.Gameplay'
    local FinishScene = require 'Scenes.Finish'

    GameplayScene.hide()
    FinishScene.show(self._graduatedChildren, self._deadChildren)
end

return FinishGame