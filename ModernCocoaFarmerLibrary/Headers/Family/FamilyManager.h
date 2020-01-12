#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"
#include "Memory/ObserverPtr.h"

#include <vector>


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
      using Children = std::vector<std::unique_ptr<Child>>;

    public:
      size_t getChildCount() const { return m_children.size(); }
      observer_ptr<Child> getChild(size_t childIndex) const;

      void selectOnlyThisChild(Child& childToSelect) const;

      void applyHealthModifier(Stats::Modifier& modifier) const;
      void applySafetyModifier(Stats::Modifier& modifier) const;
      void applyEducationModifier(Stats::Modifier& modifier) const;
      void applyHappinessModifier(Stats::Modifier& modifier) const;

      Children::const_iterator begin() const { return m_children.begin(); }
      Children::const_iterator end() const { return m_children.end(); }

    private:
      Children m_children;
  };
}