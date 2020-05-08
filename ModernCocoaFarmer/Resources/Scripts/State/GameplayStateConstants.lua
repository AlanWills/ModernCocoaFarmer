local GameplayStateConstants = 
{
    SAVE_DIRECTORY = path.combine(Resources.getResourcesDirectory(), "Data", "AppData", "Save"),
    DEFAULT_PERSISTENCE_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Persistence", "Persistence.xml"),
    DEFAULT_TIME_MANAGER_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Time", "TimeManager.asset"),
    DEFAULT_MONEY_MANAGER_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Money", "MoneyManager.asset"),
    DEFAULT_FAMILY_MANAGER_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Family", "FamilyManager.asset"),
    DEFAULT_LOCATIONS_MANAGER_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Locations", "LocationsManager.asset"),
    DEFAULT_NOTIFICATION_MANAGER_PATH = path.combine(Resources.getResourcesDirectory(), "Data", "Notifications", "NotificationsManager.asset"),
}

return GameplayStateConstants