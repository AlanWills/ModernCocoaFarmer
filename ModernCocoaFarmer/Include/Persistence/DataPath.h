#pragma once

#include <string>


namespace MCF::Persistence::DataPath
{
  //------------------------------------------------------------------------------------------------
  static constexpr const char DataPathDelimiter = '.';

  //------------------------------------------------------------------------------------------------
  inline std::string combine(const std::string& mainPath, const std::string& extraPath)
  {
    std::string whole;
    whole.reserve(mainPath.size() + extraPath.size() + 1);
    whole.append(mainPath);
    whole.push_back(DataPathDelimiter);
    whole.append(extraPath);
    return whole;
  }

  //------------------------------------------------------------------------------------------------
  inline void combine(std::string& mainPath, const std::string& extraPath)
  {
    mainPath.push_back(DataPathDelimiter);
    mainPath.append(extraPath);
  }

  //------------------------------------------------------------------------------------------------
  template <typename... Args>
  void combine(std::string& mainPath, const std::string& path, const Args&... paths)
  {
    combine(mainPath, path);
    combine(mainPath, paths...);
  }
}