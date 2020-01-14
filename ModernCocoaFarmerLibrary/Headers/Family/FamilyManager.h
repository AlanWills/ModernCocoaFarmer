#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"
#include "Memory/ObserverPtr.h"
#include "Events/Event.h"

#include <vector>
#include <queue>


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Family
{
  class Child;

  class FamilyManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(FamilyManager, MCFLibraryDllExport);

    private:
      using ChildrenNames = std::queue<std::string>;
      using Children = std::vector<std::unique_ptr<Child>>;
      using ChildAddedEvent = CelesteEngine::Event<Child&>;

    public:
      size_t getChildCount() const { return m_children.size(); }
      observer_ptr<Child> getChild(size_t childIndex) const;

      void addChild();
      void selectOnlyThisChild(Child& childToSelect) const;

      void applyHealthModifier(Stats::Modifier& modifier) const;
      void applySafetyModifier(Stats::Modifier& modifier) const;
      void applyEducationModifier(Stats::Modifier& modifier) const;
      void applyHappinessModifier(Stats::Modifier& modifier) const;
      void applyDailyModifiers() const;

      Children::const_iterator begin() const { return m_children.begin(); }
      Children::const_iterator end() const { return m_children.end(); }

      static const char* const DAILY_HEALTH_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_SAFETY_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_EDUCATION_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_HAPPINESS_MODIFIER_ATTRIBUTE_NAME;
      static const char* const CHILDREN_NAMES_ELEMENT_NAME;
      static const char* const NAME_ELEMENT_NAME;

    private:
      Stats::Modifier& m_dailyHealthModifier;
      Stats::Modifier& m_dailySafetyModifier;
      Stats::Modifier& m_dailyEducationModifier;
      Stats::Modifier& m_dailyHappinessModifier;

      ChildrenNames m_childrenNames;
      Children m_children;
      ChildAddedEvent m_childAddedEvent;
  };
}