#include "Utils/LocaTokens.h"
#include "Utils/StringUtils.h"

#include <algorithm>


namespace MCF::Utils
{
  //------------------------------------------------------------------------------------------------
  std::string substituteLocaTokens(std::string originalString, const LocaTokens& locaTokens)
  {
    for (const auto& locaToken : locaTokens)
    {
      CelesteEngine::replaceAll(originalString, locaToken.first, locaToken.second);
    }

    return originalString;
  }
}