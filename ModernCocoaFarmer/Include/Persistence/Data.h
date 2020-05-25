#pragma once

#include <glm/glm.hpp>
#include <variant>
#include <string>


namespace MCF::Persistence
{
  using Data = std::variant<bool, int, unsigned int, float, std::string, glm::vec3>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct data_return { using type = T; };

  //------------------------------------------------------------------------------------------------
  template <>
  struct data_return<std::string> { using type = const std::string&; };

  //------------------------------------------------------------------------------------------------
  template <>
  struct data_return<glm::vec3> { using type = const glm::vec3&; };
}