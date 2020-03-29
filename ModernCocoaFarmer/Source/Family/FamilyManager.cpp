#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Family/DataSources.h"
#include "Persistence/DataObjectHandle.h"
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

    if (error == Celeste::XML::XMLValueError::kError)
    {
      ASSERT_FAIL();
      return false;
    }

    for (const std::string& name : names)
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
    updateDataStore();

    m_childAddedEvent.invoke(*m_children.back());
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::selectOnlyThisChild(Child& childToSelect)
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

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::deselectOnlyThisChild(Child& childToSelect)
  {
    for (const auto& child : m_children)
    {
      if (child.get() == &childToSelect)
      {
        if (childToSelect.isSelected())
        {
          childToSelect.setSelected(false);
        }
      }
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyHealthModifier(const Stats::Modifier& modifier)
  {
    for (const auto& child : m_children)
    {
      child->applyHealthModifier(modifier);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applySafetyModifier(const Stats::Modifier& modifier)
  {
    for (const auto& child : m_children)
    {
      child->applySafetyModifier(modifier);
    }
  
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyEducationModifier(const Stats::Modifier& modifier)
  {
    for (const auto& child : m_children)
    {
      child->applyEducationModifier(modifier);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyHappinessModifier(const Stats::Modifier& modifier)
  {
    for (const auto& child : m_children)
    {
      child->applyHappinessModifier(modifier);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyDailyModifiers()
  {
    // Prevent multiple data store updates in one go
    m_suspendDataStoreUpdates = true;

    applyHealthModifier(m_dailyHealthModifier);
    applyEducationModifier(m_dailyEducationModifier);
    applySafetyModifier(m_dailySafetyModifier);
    applyHappinessModifier(m_dailyHappinessModifier);

    m_suspendDataStoreUpdates = false;
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::setDataStore(observer_ptr<Persistence::DataStore> dataStore)
  {
    m_dataStore = dataStore;
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::updateDataStore()
  {
    if (m_dataStore != nullptr && !m_suspendDataStoreUpdates)
    {
      for (const auto& child : m_children)
      {
        std::string childKey(DataSources::CHILDREN);
        childKey.push_back('.');
        childKey.append(child->getName());

        Persistence::DataObjectHandle childObject(*m_dataStore, childKey);
        childObject.set(DataSources::HEALTH, child->getHealth());
        childObject.set(DataSources::SAFETY, child->getSafety());
        childObject.set(DataSources::EDUCATION, child->getEducation());
        childObject.set(DataSources::HAPPINESS, child->getHappiness());
        childObject.set(DataSources::IS_SELECTED, child->isSelected());
        childObject.set(DataSources::IS_AT_LOCATION, child->isAtLocation());
        childObject.set(DataSources::CURRENT_LOCATION, child->getCurrentLocation());
      }
    }
  }
}