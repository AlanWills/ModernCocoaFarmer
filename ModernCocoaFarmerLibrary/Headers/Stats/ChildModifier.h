#pragma once

#include "MCFLibraryDllExport.h"
#include "Stats/Modifier.h"


namespace MCF
{
  namespace Stats
  {
    class ChildModifier : public Modifier
    {
      DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(ChildModifier, MCFLibraryDllExport);

      public:
        bool getAppliesToAllChildren() const { return m_appliesToAllChildren.getValue(); }

        static const std::string APPLIES_TO_ALL_CHILDREN_FIELD_NAME;

      private:
        Celeste::ValueField<bool>& m_appliesToAllChildren;
    };
  }
}