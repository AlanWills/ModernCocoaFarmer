#pragma once

#include <string>


namespace MCF::Persistence::DataPath
{
  //------------------------------------------------------------------------------------------------
  static constexpr const char DataPathDelimiter = '.';

  //------------------------------------------------------------------------------------------------
  std::string combine(const std::string& mainPath, const std::string& extraPath)
  {
    return mainPath + extraPath;
  }

  //------------------------------------------------------------------------------------------------
  void combine(std::string& mainPath, const std::string& extraPath)
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