-- Bootstrap
require 'Utility.DataPath'
math.randomseed(os.time())

-- Game
local Splash = require 'Scenes.Splash'
local Loading = require 'Scenes.Loading'
local Gameplay = require 'Scenes.Gameplay'  -- Think this might be needed to prevent GC, but I'm not sure

Mouse.setCursor(path.combine("Textures", "UI", "Utility", "Cursor.png"))
Splash.new()

-- Pre-load the loading scene
Loading.new()