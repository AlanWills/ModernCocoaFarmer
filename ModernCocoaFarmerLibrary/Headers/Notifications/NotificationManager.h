#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"


namespace MCF::Notifications
{
  class Notification;

  class NotificationManager : public Celeste::ScriptableObject
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(NotificationManager, MCFLibraryDllExport);

    public:
      using NotificationSentEvent = Celeste::Event<const Notification&>;

      void sendNotification(const Notification& notification) const;

      const NotificationSentEvent& getNotificationSentEvent() const { return m_onNotificationSentEvent; }

    private:
      NotificationSentEvent m_onNotificationSentEvent;
  };
}