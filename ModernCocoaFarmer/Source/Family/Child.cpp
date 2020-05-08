#include "Family/Child.h"
#include "Family/DataSources.h"
#include "Stats/DataSources.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Stats/Modifier.h"
#include "Persistence/DataObjectHandle.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(Child);

  //------------------------------------------------------------------------------------------------
  const float STAT_MAX_VALUE = 100.0f;
  const char* const Child::HEALTH_FIELD_NAME = "health";
  const char* const Child::SAFETY_FIELD_NAME = "safety";
  const char* const Child::EDUCATION_FIELD_NAME = "education";
  const char* const Child::HAPPINESS_FIELD_NAME = "happiness";
  const char* const Child::CURRENT_LOCATION_FIELD_NAME = "current_location";
  const char* const Child::TIME_AT_LOCATION_FIELD_NAME = "time_at_location";

  //------------------------------------------------------------------------------------------------
  Child::Child() :
    m_health(createValueField<float>(HEALTH_FIELD_NAME, STAT_MAX_VALUE)),
    m_safety(createValueField<float>(SAFETY_FIELD_NAME, STAT_MAX_VALUE)),
    m_education(createValueField<float>(EDUCATION_FIELD_NAME, 0)),
    m_happiness(createValueField<float>(HAPPINESS_FIELD_NAME, STAT_MAX_VALUE)),
    m_currentLocation(createReferenceField<std::string>(CURRENT_LOCATION_FIELD_NAME)),
    m_timeAtLocation(createValueField<float>(TIME_AT_LOCATION_FIELD_NAME)),
    m_isSelected(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Child::setDataStore(Persistence::DataStore& dataStore)
  {
    std::string key = DataSources::CHILDREN;
    key.push_back('.');
    key.append(getName());

    m_dataObjectHandle = std::make_unique<Persistence::DataObjectHandle>(dataStore, key);
    updateDataObject();
  }

  //------------------------------------------------------------------------------------------------
  void Child::setHealth(float health)
  { 
    m_health.setValue(health);
    m_dataObjectHandle->set(Stats::DataSources::HEALTH, getHealth());
  }

  //------------------------------------------------------------------------------------------------
  void Child::setSafety(float safety) 
  { 
    m_safety.setValue(safety);
    m_dataObjectHandle->set(Stats::DataSources::SAFETY, getSafety());
  }

  //------------------------------------------------------------------------------------------------
  void Child::setEducation(float education) 
  { 
    m_education.setValue(education);
    m_dataObjectHandle->set(Stats::DataSources::EDUCATION, getEducation());
  }

  //------------------------------------------------------------------------------------------------
  void Child::setHappiness(float happiness) 
  { 
    m_happiness.setValue(happiness);
    m_dataObjectHandle->set(Stats::DataSources::HAPPINESS, getHappiness());
  }

  //------------------------------------------------------------------------------------------------
  void Child::setCurrentLocation(const std::string& currentLocation) 
  { 
    m_currentLocation.setValue(currentLocation);
    m_dataObjectHandle->set(DataSources::CURRENT_LOCATION, getCurrentLocation());
  }
  
  //------------------------------------------------------------------------------------------------
  void Child::setTimeAtLocation(float timeAtLocation) 
  {
    m_timeAtLocation.setValue(timeAtLocation);
    m_dataObjectHandle->set(DataSources::TIME_AT_LOCATION, getTimeAtLocation());
  }

  //------------------------------------------------------------------------------------------------
  void Child::setSelected(bool selected)
  { 
    m_isSelected = selected;
    m_dataObjectHandle->set(DataSources::IS_SELECTED, isSelected());
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHealthModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_health, Stats::DataSources::HEALTH);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applySafetyModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_safety, Stats::DataSources::SAFETY);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyEducationModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_education, Stats::DataSources::EDUCATION);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHappinessModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_happiness, Stats::DataSources::HAPPINESS);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyModifier(
    const Stats::Modifier& modifier, 
    Celeste::ValueField<float>& attributeToModify,
    const std::string& dataSource)
  {
    if (modifier.getChangeType() == Stats::ChangeType::kAbsolute)
    {
      // Absolute values aren't normalized - this doesn't make sense
      attributeToModify.setValue(modifier.getAmount());
    }
    else if (modifier.getChangeType() == Stats::ChangeType::kDelta)
    {
      attributeToModify.setValue(attributeToModify.getValue() + modifier.getNormalizedAmount());
    }
    else
    {
      ASSERT_FAIL();
    }

    attributeToModify.setValue(std::min(attributeToModify.getValue(), STAT_MAX_VALUE));
    m_dataObjectHandle->set(dataSource, attributeToModify.getValue());
  }

  //------------------------------------------------------------------------------------------------
  void Child::updateDataObject()
  {
    m_dataObjectHandle->set(Stats::DataSources::HEALTH, getHealth());
    m_dataObjectHandle->set(Stats::DataSources::SAFETY, getSafety());
    m_dataObjectHandle->set(Stats::DataSources::EDUCATION, getEducation());
    m_dataObjectHandle->set(Stats::DataSources::HAPPINESS, getHappiness());
    m_dataObjectHandle->set(DataSources::CURRENT_LOCATION, getCurrentLocation());
    m_dataObjectHandle->set(DataSources::TIME_AT_LOCATION, getTimeAtLocation());
    m_dataObjectHandle->set(DataSources::IS_SELECTED, isSelected());
  }
}