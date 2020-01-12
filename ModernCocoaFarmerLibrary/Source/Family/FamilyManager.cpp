#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(FamilyManager);

  //------------------------------------------------------------------------------------------------
  const char* const FamilyManager::DAILY_HEALTH_MODIFIER_ATTRIBUTE_NAME = "daily_health_modifier";
  const char* const FamilyManager::DAILY_SAFETY_MODIFIER_ATTRIBUTE_NAME = "daily_safety_modifier";
  const char* const FamilyManager::DAILY_EDUCATION_MODIFIER_ATTRIBUTE_NAME = "daily_education_modifier";
  const char* const FamilyManager::DAILY_HAPPINESS_MODIFIER_ATTRIBUTE_NAME = "daily_happiness_modifier";

  //------------------------------------------------------------------------------------------------
  FamilyManager::FamilyManager() :
    m_dailyHealthModifier(createScriptableObject<Stats::Modifier>("DailyHealthModifier")),
    m_dailySafetyModifier(createScriptableObject<Stats::Modifier>("DailySafetyModifier")),
    m_dailyEducationModifier(createScriptableObject<Stats::Modifier>("DailyEducationModifier")),
    m_dailyHappinessModifier(createScriptableObject<Stats::Modifier>("DailyHappinessModifier")),
    m_children(),
    m_childAddedEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getChild(size_t index) const
  {
    return index < getChildCount() ? m_children[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::addChild(std::unique_ptr<Child>&& child)
  {
    m_children.push_back(child);
    m_childAddedEvent.invoke(*m_children.back());
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::selectOnlyThisChild(Child& childToSelect) const
  {
    for (const auto& child : m_children)
    {
      if (child.get() == &childToSelect)
      {
        if (!childToSelect.isSelected())
        {
          childToSelect.setSelected(true);
        }
      }
      else
      {
        if (child->isSelected())
        {
          child->setSelected(false);
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyHealthModifier(Stats::Modifier& modifier) const
  {
    for (const auto& child : m_children)
    {
      child->applyHealthModifier(modifier);
    }
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applySafetyModifier(Stats::Modifier& modifier) const
  {
    for (const auto& child : m_children)
    {
      child->applySafetyModifier(modifier);
    }
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyEducationModifier(Stats::Modifier& modifier) const
  {
    for (const auto& child : m_children)
    {
      child->applyEducationModifier(modifier);
    }
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyHappinessModifier(Stats::Modifier& modifier) const
  {
    for (const auto& child : m_children)
    {
      child->applyHappinessModifier(modifier);
    }
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyDailyModifiers() const
  {
    applyHealthModifier(m_dailyHealthModifier);
    applyEducationModifier(m_dailyEducationModifier);
    applySafetyModifier(m_dailySafetyModifier);
    applyHappinessModifier(m_dailyHappinessModifier);
  }
}


FamilyManagerScriptCommands - addChild, applyDailyModifiers
GameplayScreen - add initial two children, hook up daily modifiers
Add daily modifier assets - figure out how scriptable object loading works...
Hook up addChildEvent to UI
Child expelled from school - they lose all education (have to be at school)