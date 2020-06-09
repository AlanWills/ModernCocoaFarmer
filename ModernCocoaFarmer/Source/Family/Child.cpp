#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"
#include "Family/DataSources.h"
#include "Stats/DataSources.h"
#include "Stats/Modifier.h"
#include "Data/DataSystem.h"
#include "Data/ObjectRef.h"
#include "Persistence/DataPath.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(Child);

  //------------------------------------------------------------------------------------------------
  const float Child::MAX_STAT_VALUE = 100.0f;
  const char* const Child::HEALTH_FIELD_NAME = "health";
  const char* const Child::SAFETY_FIELD_NAME = "safety";
  const char* const Child::EDUCATION_FIELD_NAME = "education";
  const char* const Child::HAPPINESS_FIELD_NAME = "happiness";
  const char* const Child::CURRENT_LOCATION_FIELD_NAME = "current_location";
  const char* const Child::TIME_AT_LOCATION_FIELD_NAME = "time_at_location";
  const char* const Child::STATE_FIELD_NAME = "state";

  //------------------------------------------------------------------------------------------------
  Child::Child() :
    m_health(createValueField<float>(HEALTH_FIELD_NAME, MAX_STAT_VALUE)),
    m_safety(createValueField<float>(SAFETY_FIELD_NAME, MAX_STAT_VALUE)),
    m_education(createValueField<float>(EDUCATION_FIELD_NAME, 0)),
    m_happiness(createValueField<float>(HAPPINESS_FIELD_NAME, MAX_STAT_VALUE)),
    m_currentLocation(createReferenceField<std::string>(CURRENT_LOCATION_FIELD_NAME)),
    m_timeAtLocation(createValueField<float>(TIME_AT_LOCATION_FIELD_NAME)),
    m_state(createValueField<ChildState>(STATE_FIELD_NAME)),
    m_isSelected(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Child::setDataSystem(Data::DataSystem& dataSystem)
  {
    m_childObjectRef = std::make_unique<Data::ObjectRef>(dataSystem, Persistence::DataPath::combine(DataSources::CHILDREN, getName()));
    updateDataObject();
  }

  //------------------------------------------------------------------------------------------------
  void Child::setHealth(float health)
  { 
    setStat(health, m_health, Stats::DataSources::HEALTH);
  }

  //------------------------------------------------------------------------------------------------
  void Child::setSafety(float safety) 
  { 
    setStat(safety, m_safety, Stats::DataSources::SAFETY);
  }

  //------------------------------------------------------------------------------------------------
  void Child::setEducation(float education) 
  { 
    setStat(education, m_education, Stats::DataSources::EDUCATION);
  }

  //------------------------------------------------------------------------------------------------
  void Child::setHappiness(float happiness) 
  { 
    setStat(happiness, m_happiness, Stats::DataSources::HAPPINESS);
  }

  //------------------------------------------------------------------------------------------------
  void Child::setCurrentLocation(const std::string& currentLocation) 
  { 
    if (isActivated())
    {
      m_currentLocation.setValue(currentLocation);
      m_childObjectRef->set(DataSources::CURRENT_LOCATION, getCurrentLocation());
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void Child::setTimeAtLocation(float timeAtLocation) 
  {
    if (isActivated())
    {
      m_timeAtLocation.setValue(timeAtLocation);
      m_childObjectRef->set(DataSources::TIME_AT_LOCATION, getTimeAtLocation() * 100);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Child::setSelected(bool selected)
  { 
    if (isActivated())
    {
      m_isSelected = selected;
      m_childObjectRef->set(DataSources::IS_SELECTED, isSelected());
    }
  }

  //------------------------------------------------------------------------------------------------
  void Child::activate()
  {
    setState(ChildState::kActive);
  }

  //------------------------------------------------------------------------------------------------
  bool Child::canGraduate() const
  { 
    return getEducation() >= MAX_STAT_VALUE; 
  }

  //------------------------------------------------------------------------------------------------
  void Child::graduate()
  {
    setState(ChildState::kGraduated);
  }

  //------------------------------------------------------------------------------------------------
  void Child::die()
  {
    setState(ChildState::kDead);
  }

  //------------------------------------------------------------------------------------------------
  void Child::setState(ChildState childState)
  {
    m_state.setValue(childState);
    m_childObjectRef->set(DataSources::IS_ACTIVATED, childState == ChildState::kActive);
    m_childObjectRef->set(DataSources::IS_GRADUATED, childState == ChildState::kGraduated);
    m_childObjectRef->set(DataSources::IS_DEAD, childState == ChildState::kDead);
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
  void Child::setStat(
    float value,
    Celeste::ValueField<float>& attributeToModify,
    const std::string& dataSource)
  {
    if (isActivated())
    {
      attributeToModify.setValue(std::clamp(value, 0.0f, MAX_STAT_VALUE));
      m_childObjectRef->set(dataSource, attributeToModify.getValue());
    }
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
      setStat(modifier.getAmount(), attributeToModify, dataSource);
    }
    else if (modifier.getChangeType() == Stats::ChangeType::kDelta)
    {
      setStat(attributeToModify.getValue() + modifier.getNormalizedAmount(), attributeToModify, dataSource);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Child::updateDataObject()
  {
    m_childObjectRef->set(DataSources::CHILD_NAME, getName());
    m_childObjectRef->set(Stats::DataSources::HEALTH, getHealth());
    m_childObjectRef->set(Stats::DataSources::SAFETY, getSafety());
    m_childObjectRef->set(Stats::DataSources::EDUCATION, getEducation());
    m_childObjectRef->set(Stats::DataSources::HAPPINESS, getHappiness());
    m_childObjectRef->set(DataSources::CURRENT_LOCATION, getCurrentLocation());
    m_childObjectRef->set(DataSources::TIME_AT_LOCATION, getTimeAtLocation());
    m_childObjectRef->set(DataSources::IS_SELECTED, isSelected());
    m_childObjectRef->set(DataSources::IS_ACTIVATED, isActivated());
    m_childObjectRef->set(DataSources::IS_GRADUATED, isGraduated());
    m_childObjectRef->set(DataSources::IS_DEAD, isDead());
  }
}