#pragma once

#include <variant>
#include <string>


namespace MCF::Persistence
{
  using Data = std::variant<bool, int, unsigned int, float, std::string>;
}