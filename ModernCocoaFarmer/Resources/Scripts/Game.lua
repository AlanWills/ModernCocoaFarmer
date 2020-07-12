-- Bootstrap
require 'Utility.DataPath'
math.randomseed(os.time())

-- Game
local Splash = require 'Scenes.Splash'
local Loading = require 'Scenes.Loading'

Splash.new()

-- Pre-load the loading scene
Loading.new()