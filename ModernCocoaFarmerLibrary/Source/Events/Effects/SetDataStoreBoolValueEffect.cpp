#include "Events/Effects/SetDataStoreBoolValueEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Persistence/DataStore.h"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace MCF::Events::Effects
{
  REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(SetDataStoreBoolValueEffect);

  //------------------------------------------------------------------------------------------------
  const char* const SetDataStoreBoolValueEffect::DATA_STORE_PATH_ATTRIBUTE_NAME = "data_store_path";
  const char* const SetDataStoreBoolValueEffect::VALUE_NAME_ATTRIBUTE_NAME = "value_name";
  const char* const SetDataStoreBoolValueEffect::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  SetDataStoreBoolValueEffect::SetDataStoreBoolValueEffect() :
    m_dataStorePath(createReferenceField<std::string>(DATA_STORE_PATH_ATTRIBUTE_NAME)),
    m_valueName(createReferenceField<std::string>(VALUE_NAME_ATTRIBUTE_NAME)),
    m_value(createValueField<bool>(VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SetDataStoreBoolValueEffect::trigger(
    Money::MoneyManager&,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(getDataStorePath());
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    Persistence::DataStore dataStore = Persistence::DataStore::deserialize(*data->getDocumentRoot());
    dataStore.set<bool>(getValueName(), getValue());

    data->getDocument().Clear();
    tinyxml2::XMLElement* rootElement = data->getDocument().NewElement("DataStore");
    data->getDocument().InsertFirstChild(rootElement);
    dataStore.serialize(*rootElement);
  }
}