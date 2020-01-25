#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class ModifyChildAtLocationStatEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(ModifyChildAtLocationStatEffect, MCFLibraryDllExport);

    public:
      const std::string& getModifierPath() const { return m_modifierPath.getValue(); }
      const std::string& getStat() const { return m_stat.getValue(); }
      const std::string& getLocation() const { return m_location.getValue(); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager&) const override;

      static const char* const MODIFIER_PATH_ATTRIBUTE_NAME;
      static const char* const STAT_ATTRIBUTE_NAME;
      static const char* const LOCATION_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_modifierPath;
      CelesteEngine::ReferenceField<std::string>& m_stat;
      CelesteEngine::ReferenceField<std::string>& m_location;
  };
}