#include "Notifications/Notification.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Serialization/Serializers.h"


namespace MCF::Notifications
{
  REGISTER_SCRIPTABLE_OBJECT(Notification);

  //------------------------------------------------------------------------------------------------
  const char* const Notification::DESCRIPTION_ATTRIBUTE_NAME = "description";
  const char* const Notification::ICON_ATTRIBUTE_NAME = "icon";

  //------------------------------------------------------------------------------------------------
  Notification::Notification() :
    m_description(createReferenceField<std::string>(DESCRIPTION_ATTRIBUTE_NAME)),
    m_icon(createValueField<observer_ptr<Celeste::Resources::Texture2D>>(ICON_ATTRIBUTE_NAME))
  {
  }
}