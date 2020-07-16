-- Bootstrap
require 'Utility.DataPath'
math.randomseed(os.time())

-- Game
local MenuMusic = require 'Scenes.MenuMusic'
local Splash = require 'Scenes.Splash'
local Loading = require 'Scenes.Loading'

MenuMusic.show()
Splash.show()

-- Pre-load the loading scene
Loading.new()