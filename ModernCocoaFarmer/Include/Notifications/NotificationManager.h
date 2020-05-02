#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "CelesteStl/Memory/ObserverPtr.h"
#include "Events/Event.h"


namespace MCF::Notifications
{
  class Notification;

  class NotificationManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(NotificationManager, MCFLibraryDllExport);

    public:
      using NotificationSentEvent = Celeste::Event<const Notification&>;

      size_t getNotificationCount() const { return m_notifications.size(); }
      MCFLibraryDllExport observer_ptr<const Notification> getNotification(size_t index) const;

      MCFLibraryDllExport void sendNotification(std::unique_ptr<Notification>&& notification);
      MCFLibraryDllExport void removeNotification(const Notification& notification);

      const NotificationSentEvent& getNotificationSentEvent() const { return m_onNotificationSentEvent; }

      static const char* const NOTIFICATION_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using Notifications = std::vector<std::reference_wrapper<const Notification>>;

      Notifications m_notifications;
      NotificationSentEvent m_onNotificationSentEvent;
  };
}