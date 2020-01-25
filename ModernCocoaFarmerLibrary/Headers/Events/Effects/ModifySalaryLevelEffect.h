#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class ModifySalaryLevelEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(ModifySalaryLevelEffect, MCFLibraryDllExport);

    public:
      int getModifier() const { return m_modifier.getValue(); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager& notificationManager) const override;

      static const char* const MODIFIER_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ValueField<int>& m_modifier;
  };
}