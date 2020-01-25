#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Notifications
{
  class Notification;
}

namespace MCF::Events::Effects
{
  class SendNotification : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(SendNotification, MCFLibraryDllExport);

    public:
      const Notifications::Notification& getNotification() const { return m_notification; }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager) const override;

      static const char* const NOTIFICATION_ATTRIBUTE_NAME;

    private:
      Notifications::Notification& m_notification;
  };
}