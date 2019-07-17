local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Screens", "Gameplay.asset")

if Resources.isDataLoaded(screenPath) then
    Resources.unloadData(screenPath)
end

Screen.load(screenPath)