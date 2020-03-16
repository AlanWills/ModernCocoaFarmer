#pragma once

#include "Bindings/DataBindingGenerators.h"
#include "Stats/ModifierEnums.h"

namespace MCF
{
  namespace Bindings
  {
    namespace Stats
    {
      //------------------------------------------------------------------------------------------------
      template <bool is_reference>
      struct Celeste::Bindings::DataBindingGenerator<MCF::Stats::ChangeType, is_reference>
      {
        DECLARE_DATA_BINDING_GENERATOR(MCF::Stats::ChangeType)

        private:
          static void generatePropertyBinding(
            const std::string& variableName,
            typename choose_class<static_cast<bool>(is_reference), const MCF::Stats::ChangeType&, MCF::Stats::ChangeType>::type value,
            std::string& output)
          {
            output.append("public ChangeType ");
            output.append(variableName);
            output.append(" { get; set; } = ChangeType.");
            output.append(Celeste::to_string(value));
            output.push_back(';');
          }
      };

      //------------------------------------------------------------------------------------------------
      template <bool is_reference>
      struct Celeste::Bindings::DataBindingGenerator<MCF::Stats::Occurrence, is_reference>
      {
        DECLARE_DATA_BINDING_GENERATOR(MCF::Stats::Occurrence)

        private:
          static void generatePropertyBinding(
            const std::string& variableName,
            typename choose_class<static_cast<bool>(is_reference), const MCF::Stats::Occurrence&, MCF::Stats::Occurrence>::type value,
            std::string& output)
          {
            output.append("public Occurrence ");
            output.append(variableName);
            output.append(" { get; set; } = Occurrence.");
            output.append(Celeste::to_string(value));
            output.push_back(';');
          }
      };
    }
  }
}