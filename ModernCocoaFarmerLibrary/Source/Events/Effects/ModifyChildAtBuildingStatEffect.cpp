#include "Events/Effects/ModifyChildAtBuildingStatEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Stats/Modifier.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyChildAtBuildingStatEffect);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyChildAtBuildingStatEffect::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";
  const char* const ModifyChildAtBuildingStatEffect::STAT_ATTRIBUTE_NAME = "stat";
  const char* const ModifyChildAtBuildingStatEffect::BUILDING_ATTRIBUTE_NAME = "building";

  //------------------------------------------------------------------------------------------------
  ModifyChildAtBuildingStatEffect::ModifyChildAtBuildingStatEffect() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME)),
    m_stat(createReferenceField<std::string>(STAT_ATTRIBUTE_NAME)),
    m_building(createReferenceField<std::string>(BUILDING_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifyChildAtBuildingStatEffect::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager) const
  {
    ASSERT_FAIL_MSG("TODO - Add ability to know which building the children are at.");
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr)

    if (modifier != nullptr)
    {
      const std::string& stat = getStat();

      if (stat == Family::Child::HEALTH_FIELD_NAME)
      {
      }
      else if (stat == Family::Child::EDUCATION_FIELD_NAME)
      {
      }
      else if (stat == Family::Child::SAFETY_FIELD_NAME)
      {
      }
      else if (stat == Family::Child::HAPPINESS_FIELD_NAME)
      {
      }
      else
      {
        ASSERT_FAIL();
      }
    }
  }
}