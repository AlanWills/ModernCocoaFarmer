#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class ModifyMoney : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(ModifyMoney, MCFLibraryDllExport);

    public:
      const std::string& getModifierPath() const { return m_modifierPath.getValue(); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager& notificationManager) const override;

      static const char* const MODIFIER_PATH_ATTRIBUTE_NAME;

    private:
      Celeste::ReferenceField<std::string>& m_modifierPath;
  };
}