---------------------------------------------------------------------------------
local MenuMusic =
{
    MUSIC_MUSIC_SCENE_PATH = path.combine("Scenes", "MenuMusic.scene"),
    MENU_MUSIC_ROOT_NAME = "MenuMusic",
}

---------------------------------------------------------------------------------
function MenuMusic.show()
    if MenuMusic._root == nil then
        Scene.load(MenuMusic.MUSIC_MUSIC_SCENE_PATH)
        MenuMusic._root = GameObject.find(MenuMusic.MENU_MUSIC_ROOT_NAME)
        MenuMusic._audioSource = MenuMusic._root:findComponent("AudioSource")
    end
end

---------------------------------------------------------------------------------
function MenuMusic.hide()
    if MenuMusic._root ~= nil then
        MenuMusic._root:destroy()
        MenuMusic._root = nil
        MenuMusic._audioSource = nil
    end
end

---------------------------------------------------------------------------------
function MenuMusic.decreaseVolume(amount)
    if MenuMusic._audioSource ~= nil then
        local currentVolume = MenuMusic._audioSource:getVolume()
        MenuMusic._audioSource:setVolume(math.max(0, currentVolume - amount))
    end
end

return MenuMusic
