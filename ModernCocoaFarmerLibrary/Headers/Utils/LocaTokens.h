#pragma once

#include "MCFLibraryDllExport.h"

#include <string>
#include <unordered_map>


namespace MCF::Utils
{
  using LocaTokens = std::unordered_map<std::string, std::string>;

  std::string substituteLocaTokens(std::string originalString, const LocaTokens& locaTokens);
}