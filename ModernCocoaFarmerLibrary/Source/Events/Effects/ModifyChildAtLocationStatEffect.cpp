#include "Events/Effects/ModifyChildAtLocationStatEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Stats/Modifier.h"
#include "Locations/LocationsManager.h"
#include "Locations/Location.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyChildAtLocationStatEffect);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyChildAtLocationStatEffect::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";
  const char* const ModifyChildAtLocationStatEffect::STAT_ATTRIBUTE_NAME = "stat";
  const char* const ModifyChildAtLocationStatEffect::LOCATION_ATTRIBUTE_NAME = "location";

  //------------------------------------------------------------------------------------------------
  ModifyChildAtLocationStatEffect::ModifyChildAtLocationStatEffect() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME)),
    m_stat(createReferenceField<std::string>(STAT_ATTRIBUTE_NAME)),
    m_location(createReferenceField<std::string>(LOCATION_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifyChildAtLocationStatEffect::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager&) const
  {
    observer_ptr<Locations::Location> location = locationsManager.getLocation(getLocation());
    if (location == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    auto foundChildIt = std::find_if(familyManager.begin(), familyManager.end(), 
      [location](const std::unique_ptr<Family::Child>& child)
      {
        return child->getCurrentLocation() == location->getName();
      });

    if (foundChildIt == familyManager.end())
    {
      ASSERT_FAIL();
      return;
    }
    
    Family::Child& child = **foundChildIt;

    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr)

    if (modifier != nullptr)
    {
      const std::string& stat = getStat();

      if (stat == Family::Child::HEALTH_FIELD_NAME)
      {
        child.applyHealthModifier(*modifier);
      }
      else if (stat == Family::Child::EDUCATION_FIELD_NAME)
      {
        child.applyEducationModifier(*modifier);
      }
      else if (stat == Family::Child::SAFETY_FIELD_NAME)
      {
        child.applySafetyModifier(*modifier);
      }
      else if (stat == Family::Child::HAPPINESS_FIELD_NAME)
      {
        child.applyHappinessModifier(*modifier);
      }
      else
      {
        ASSERT_FAIL();
      }
    }
  }
}