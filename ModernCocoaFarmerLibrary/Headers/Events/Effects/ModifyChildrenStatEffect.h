#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class ModifyChildrenStatEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(ModifyChildrenStatEffect, MCFLibraryDllExport);

    public:
      const std::string& getModifierPath() const { return m_modifierPath.getValue(); }
      const std::string& getStat() const { return m_stat.getValue(); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager& notificationManager) const override;

      static const char* const MODIFIER_PATH_ATTRIBUTE_NAME;
      static const char* const STAT_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_modifierPath;
      CelesteEngine::ReferenceField<std::string>& m_stat;
  };
}