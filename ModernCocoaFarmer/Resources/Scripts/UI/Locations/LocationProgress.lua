local LocationProgress =
{
    LOCATION_PROGRESS_PREFAB_PATH = path.combine("Prefabs", "UI", "Locations", "LocationProgress.prefab"),
    CHILD_NAME_TEXT = "ChildNameText",
}

----------------------------------------------------------------------------------------
function LocationProgress:new(childName, screen)
    local locationProgressPrefab = Resources.loadPrefab(self.LOCATION_PROGRESS_PREFAB_PATH) 
    self.gameObject = locationProgressPrefab:instantiate(screen)
    self.gameObject:findChildGameObject(self.CHILD_NAME_TEXT):findComponent("TextRenderer"):setText(childName)

    self._progressBar = self.gameObject:findComponent("ProgressBar")
end

----------------------------------------------------------------------------------------
function LocationProgress:updateUI(progress)
    self._progressBar:setProgress(progress)
end

return LocationProgress