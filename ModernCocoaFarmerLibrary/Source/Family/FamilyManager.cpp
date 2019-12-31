#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(FamilyManager);

  //------------------------------------------------------------------------------------------------
  FamilyManager::FamilyManager() :
    m_children()
  {
    m_children.reserve(7);

    for (size_t i = 0; i < 7; ++i)
    {
      m_children.emplace_back(ScriptableObject::create<Child>("Child " + std::to_string(i)));
    }
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Child> FamilyManager::getChild(size_t index) const
  {
    return index < getChildCount() ? m_children[index].get() : nullptr;
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
}