#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Effects/Effect.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Effects
{
  class SetDataStoreBoolValueEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(SetDataStoreBoolValueEffect, MCFLibraryDllExport);

    public:
      const std::string& getDataStorePath() const { return m_dataStorePath.getValue(); }
      void setDataStorePath(const std::string& dataStorePath) { return m_dataStorePath.setValue(dataStorePath); }

      const std::string& getValueName() const { return m_valueName.getValue(); }
      void setValueName(const std::string& valueName) { return m_valueName.setValue(valueName); }

      bool getValue() const { return m_value.getValue(); }
      void setValue(bool defaultValue) { m_value.setValue(defaultValue); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager& notificationManager) const override;

      static const char* const DATA_STORE_PATH_ATTRIBUTE_NAME;
      static const char* const VALUE_NAME_ATTRIBUTE_NAME;
      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      Celeste::ReferenceField<std::string>& m_dataStorePath;
      Celeste::ReferenceField<std::string>& m_valueName;
      Celeste::ValueField<bool>& m_value;
  };
}