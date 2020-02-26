#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Stats/Modifier.h"
#include "XML/tinyxml2_ext.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(FamilyManager);

  //------------------------------------------------------------------------------------------------
  const char* const FamilyManager::DAILY_HEALTH_MODIFIER_ATTRIBUTE_NAME = "daily_health_modifier";
  const char* const FamilyManager::DAILY_SAFETY_MODIFIER_ATTRIBUTE_NAME = "daily_safety_modifier";
  const char* const FamilyManager::DAILY_EDUCATION_MODIFIER_ATTRIBUTE_NAME = "daily_education_modifier";
  const char* const FamilyManager::DAILY_HAPPINESS_MODIFIER_ATTRIBUTE_NAME = "daily_happiness_modifier";
  const char* const FamilyManager::CHILDREN_NAMES_ELEMENT_NAME = "ChildrenNames";
  const char* const FamilyManager::NAME_ELEMENT_NAME = "Name";

  //------------------------------------------------------------------------------------------------
  FamilyManager::FamilyManager() :
    m_dailyHealthModifier(createScriptableObject<Stats::Modifier>(DAILY_HEALTH_MODIFIER_ATTRIBUTE_NAME)),
    m_dailySafetyModifier(createScriptableObject<Stats::Modifier>(DAILY_SAFETY_MODIFIER_ATTRIBUTE_NAME)),
    m_dailyEducationModifier(createScriptableObject<Stats::Modifier>(DAILY_EDUCATION_MODIFIER_ATTRIBUTE_NAME)),
    m_dailyHappinessModifier(createScriptableObject<Stats::Modifier>(DAILY_HAPPINESS_MODIFIER_ATTRIBUTE_NAME)),
    m_childrenNames(),
    m_children(),
    m_childAddedEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool FamilyManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    Inherited::doDeserialize(element);

    std::vector<std::string> names;
    Celeste::XML::XMLValueError error = Celeste::XML::getChildElementDataAsVector(
      element,
      CHILDREN_NAMES_ELEMENT_NAME,
      NAME_ELEMENT_NAME,
      names);

    CelesteCeleste::XML::XMLValueECeleste
    {
      ASSERT_FAIL();
      return false;
    }

    for (const stCelesteme : names)
    {
      m_childrenNames.push(name);
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getChild(size_t index) const
  {
    return index < getChildCount() ? m_children[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  bool FamilyManager::hasSelectedChild() const
  {
    return std::find_if(m_children.begin(), m_children.end(), 
      [](const std::unique_ptr<Child>& child)
      {
        return child->isSelected();
      }) != m_children.end();
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getSelectedChild()
  {
    ASSERT(hasSelectedChild());
    return std::find_if(m_children.begin(), m_children.end(),
      [](const std::unique_ptr<Child>& child)
      {
        return child->isSelected();
      })->get();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::addChild()
  {
    if (m_childrenNames.empty())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string name = m_childrenNames.front();
    m_childrenNames.pop();

    m_children.push_back(ScriptableObject::create<Child>(name));
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