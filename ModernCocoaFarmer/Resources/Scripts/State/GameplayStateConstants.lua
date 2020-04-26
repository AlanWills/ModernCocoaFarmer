local GameplayStateConstants = 
{
    SAVE_DIRECTORY = path.combine("Data", "AppData", "Save"),
    DEFAULT_TIME_MANAGER_PATH = path.combine("Data", "Time", "TimeManager.asset"),
    DEFAULT_MONEY_MANAGER_PATH = path.combine("Data", "Money", "MoneyManager.asset"),
    DEFAULT_FAMILY_MANAGER_PATH = path.combine("Data", "Family", "FamilyManager.asset"),
    DEFAULT_LOCATIONS_MANAGER_PATH = path.combine("Data", "Locations", "LocationsManager.asset"),
    DEFAULT_NOTIFICATION_MANAGER_PATH = path.combine("Data", "Notifications", "NotificationsManager.asset"),
    DEFAULT_GAME_EVENT_MANAGER_PATH = path.combine("Data", "Events", "GameEventManager.asset"),
}

return GameplayStateConstants