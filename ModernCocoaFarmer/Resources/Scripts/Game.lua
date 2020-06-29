-- Bootstrap
require 'Utility.DataPath'
math.randomseed(os.time())

-- Game
local Splash = require 'Scenes.Splash'
local Loading = require 'Scenes.Loading'
Gameplay = require 'Scenes.Gameplay'  -- Do we need this to prevent GC

Mouse.setCursor(path.combine("Textures", "UI", "Utility", "Cursor.png"))
Splash.new()

-- Pre-load the loading scene
Loading.new()