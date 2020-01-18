#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class ModifyMoneyEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(ModifyMoneyEffect, MCFLibraryDllExport);

    public:
      const std::string& getModifierPath() const { return m_modifierPath.getValue(); }

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&) const override;

      static const char* const MODIFIER_PATH_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_modifierPath;
  };
}