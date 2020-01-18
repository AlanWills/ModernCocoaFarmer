#include "Events/Effects/ModifyChildrenStatEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"
#include "Family/Child.h"
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
    Family::FamilyManager& familyManager,
    Locations::LocationsManager&) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr)

      if (modifier != nullptr)
      {
        const std::string& stat = getStat();
        
        if (stat == Family::Child::HEALTH_FIELD_NAME)
        {
          familyManager.applyHealthModifier(*modifier);
        }
        else if (stat == Family::Child::EDUCATION_FIELD_NAME)
        {
          familyManager.applyEducationModifier(*modifier);
        }
        else if (stat == Family::Child::SAFETY_FIELD_NAME)
        {
          familyManager.applySafetyModifier(*modifier);
        }
        else if (stat == Family::Child::HAPPINESS_FIELD_NAME)
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