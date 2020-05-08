#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Family/DataSources.h"
#include "Stats/DataSources.h"
#include "Persistence/DataObjectHandle.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Stats/Modifier.h"
#include "XML/tinyxml2_ext.h"

using namespace Celeste::XML;


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

    XMLValueError error = getChildElementDataAsVector(
      element,
      CHILDREN_NAMES_ELEMENT_NAME,
      NAME_ELEMENT_NAME,
      m_childrenNames);

    for (const tinyxml2::XMLElement* childElement : children(element, Child::type_name()))
    {
      m_children.push_back(deserializeScriptableObject<Child>(childElement));
    }

    ASSERT(error != XMLValueError::kError);
    return error != XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::doSerialize(tinyxml2::XMLElement* element) const
  {
    tinyxml2::XMLDocument* document = element->GetDocument();

    tinyxml2::XMLElement* childrenNamesElement = document->NewElement(CHILDREN_NAMES_ELEMENT_NAME);
    element->InsertEndChild(childrenNamesElement);

    for (const std::string& name : m_childrenNames)
    {
      tinyxml2::XMLElement* childNameElement = document->NewElement(NAME_ELEMENT_NAME);
      childNameElement->SetText(name.c_str());
      childrenNamesElement->InsertEndChild(childNameElement);
    }
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getChild(size_t index) const
  {
    return index < getChildCount() ? &m_children[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::findChild(const std::string& name) const
  {
    auto foundChild = std::find_if(m_children.begin(), m_children.end(),
      [&name](Child& child)
      {
        return child.getName() == name;
      });

    return foundChild != m_children.end() ? &foundChild->get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  bool FamilyManager::hasSelectedChild() const
  {
    return std::find_if(m_children.begin(), m_children.end(), 
      [](const Child& child)
      {
        return child.isSelected();
      }) != m_children.end();
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getSelectedChild()
  {
    ASSERT(hasSelectedChild());
    return &std::find_if(m_children.begin(), m_children.end(),
      [](Child& child)
      {
        return child.isSelected();
      })->get();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::addChild()
  {
    if (!canAddChild())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string name = m_childrenNames.back();
    m_childrenNames.pop_back();
    
    m_children.push_back(createScriptableObject<Child>(name));
    m_children.back().get().setDataStore(*m_dataStore);

    updateDataStore();

    m_childAddedEvent.invoke(m_children.back());
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::selectChild(Child& childToSelect)
  {
    for (Child& child : m_children)
    {
      if (&child == &childToSelect)
      {
        if (!childToSelect.isSelected())
        {
          childToSelect.setSelected(true);
        }
      }
      else
      {
        if (child.isSelected())
        {
          child.setSelected(false);
        }
      }
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::deselectChild(Child& childToSelect)
  {
    for (Child& child : m_children)
    {
      if (&child == &childToSelect)
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
    for (Child& child : m_children)
    {
      child.applyHealthModifier(modifier);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applySafetyModifier(const Stats::Modifier& modifier)
  {
    for (Child& child : m_children)
    {
      child.applySafetyModifier(modifier);
    }
  
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyEducationModifier(const Stats::Modifier& modifier)
  {
    for (Child& child : m_children)
    {
      child.applyEducationModifier(modifier);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::applyHappinessModifier(const Stats::Modifier& modifier)
  {
    for (Child& child : m_children)
    {
      child.applyHappinessModifier(modifier);
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

    for (Child& child : m_children)
    {
      child.setDataStore(*dataStore);
    }

    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void FamilyManager::updateDataStore()
  {
    if (m_dataStore != nullptr && !m_suspendDataStoreUpdates)
    {
      bool hasSC = hasSelectedChild();
      m_dataStore->set(DataSources::HAS_SELECTED_CHILD, hasSC);
      m_dataStore->set(DataSources::SELECTED_CHILD_NAME, hasSC ? getSelectedChild()->getName() : std::string());
    }
  }
}