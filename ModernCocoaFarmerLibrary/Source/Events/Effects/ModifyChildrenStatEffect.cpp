#include "Events/Effects/ModifyChildrenStatEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"
#include "Stats/Modifier.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyChildrenStatEffect);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyChildrenStatEffect::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";
  const char* const ModifyChildrenStatEffect::STAT_ATTRIBUTE_NAME = "stat";

  //------------------------------------------------------------------------------------------------
  ModifyChildrenStatEffect::ModifyChildrenStatEffect() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME)),
    m_stat(createReferenceField<std::string>(STAT_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifyChildrenStatEffect::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr)

      if (modifier != nullptr)
      {
        const std::string& stat = getStat();
        
        if (stat == "Health")
        {
          familyManager.applyHealthModifier(*modifier);
        }
        else if (stat == "Education")
        {
          familyManager.applyEducationModifier(*modifier);
        }
        else if (stat == "Safety")
        {
          familyManager.applySafetyModifier(*modifier);
        }
        else if (stat == "Happiness")
        {
          familyManager.applyHappinessModifier(*modifier);
        }
        else
        {
          ASSERT_FAIL();
        }
      }
  }
}