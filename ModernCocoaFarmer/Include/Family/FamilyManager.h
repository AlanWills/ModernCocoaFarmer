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

namespace MCF::Persistence
{
  class DataStore;
}

namespace MCF::Family
{
  class Child;

  class FamilyManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(FamilyManager, MCFLibraryDllExport);

    private:
      using Inherited = Celeste::ScriptableObject;
      using ChildrenNames = std::queue<std::string>;
      using Children = std::vector<std::unique_ptr<Child>>;

    public:
      using ChildAddedEvent = Celeste::Event<Child&>;

      void setDataStore(observer_ptr<Persistence::DataStore> dataStore);

      size_t getChildCount() const { return m_children.size(); }
      observer_ptr<Child> getChild(size_t childIndex) const;

      bool hasSelectedChild() const;
      observer_ptr<Child> getSelectedChild();

      void addChild();
      void selectOnlyThisChild(Child& childToSelect);
      void deselectOnlyThisChild(Child& childToSelect);

      void applyHealthModifier(Stats::Modifier& modifier);
      void applySafetyModifier(Stats::Modifier& modifier);
      void applyEducationModifier(Stats::Modifier& modifier);
      void applyHappinessModifier(Stats::Modifier& modifier);
      void applyDailyModifiers();

      Children::iterator begin() { return m_children.begin(); }
      Children::iterator end() { return m_children.end(); }

      Children::const_iterator begin() const { return m_children.begin(); }
      Children::const_iterator end() const { return m_children.end(); }

      const ChildAddedEvent& getChildAddedEvent() const { return m_childAddedEvent; }

      static const char* const DAILY_HEALTH_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_SAFETY_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_EDUCATION_MODIFIER_ATTRIBUTE_NAME;
      static const char* const DAILY_HAPPINESS_MODIFIER_ATTRIBUTE_NAME;
      static const char* const CHILDREN_NAMES_ELEMENT_NAME;
      static const char* const NAME_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void updateDataStore();

      Stats::Modifier& m_dailyHealthModifier;
      Stats::Modifier& m_dailySafetyModifier;
      Stats::Modifier& m_dailyEducationModifier;
      Stats::Modifier& m_dailyHappinessModifier;

      bool m_suspendDataStoreUpdates = false;
      observer_ptr<Persistence::DataStore> m_dataStore = nullptr;

      ChildrenNames m_childrenNames;
      Children m_children;
      ChildAddedEvent m_childAddedEvent;
  };
}