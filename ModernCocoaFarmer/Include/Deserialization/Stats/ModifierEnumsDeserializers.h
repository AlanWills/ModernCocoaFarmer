#pragma once

#include "MCFLibraryDllExport.h"
#include "Deserialization/Deserializers.h"
#include "Stats/ModifierEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  MCFLibraryDllExport bool deserialize<MCF::Stats::ChangeType>(const std::string& text, MCF::Stats::ChangeType& output);
}