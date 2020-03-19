#include "GameEvents/Effects/ModifyChildrenStat.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Stats/Modifier.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyChildrenStat);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyChildrenStat::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";
  const char* const ModifyChildrenStat::STAT_ATTRIBUTE_NAME = "stat";

  //------------------------------------------------------------------------------------------------
  ModifyChildrenStat::ModifyChildrenStat() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME)),
    m_stat(createReferenceField<std::string>(STAT_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifyChildrenStat::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
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