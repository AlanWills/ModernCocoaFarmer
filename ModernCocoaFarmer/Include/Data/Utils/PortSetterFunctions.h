#pragma once

#include "Data/Ports/InputPort.h"
#include "Log/Log.h"

#include <variant>


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  template <typename VariantType, typename ReturnType, typename... Args>
  struct VariadicSetterFunctions
  {
    using Variant = VariantType;
    using Function = ReturnType(*)(Args...);

    constexpr size_t size() const { return std::variant_size<Variant>::value; }

    Function m_functions[std::variant_size<Variant>::value];
  };

  //------------------------------------------------------------------------------------------------
  template <typename SetSetterFunctions, size_t index, typename From, template <typename, typename> class Functor>
  struct SetSetterFunction
  {
    static constexpr void set(SetSetterFunctions& setterFunctions)
    {
      setterFunctions.m_functions[index] = &Functor<From, typename std::variant_alternative<index, typename SetSetterFunctions::Variant>::type>::execute;
      SetSetterFunction<SetSetterFunctions, index - 1, From, Functor>::set(setterFunctions);
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename SetSetterFunctions, typename From, template <typename, typename> class Functor>
  struct SetSetterFunction<SetSetterFunctions, 0, From, Functor>
  {
    static constexpr void set(SetSetterFunctions& setterFunctions)
    {
      setterFunctions.m_functions[0] = &Functor<From, typename std::variant_alternative<0, typename SetSetterFunctions::Variant>::type>::execute;
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename SetSetterFunctions, typename From, template <typename, typename> class Functor>
  constexpr SetSetterFunctions createSetterFunctions()
  {
    SetSetterFunctions setterFunctions = SetSetterFunctions();
    SetSetterFunction<SetSetterFunctions, setterFunctions.size() - 1, From, Functor>::set(setterFunctions);

    return setterFunctions;
  }

  //------------------------------------------------------------------------------------------------
  template <typename From, typename To>
  struct Setter
  {
    static void execute(From from, InputPort& port)
    {
      port.setValue(static_cast<To>(from));
    }
  };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<std::string, std::string> 
  { 
    static void execute(std::string from, InputPort& port) 
    { 
      port.setValue(from);
    } 
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  using SetterFunctions = MCF::Data::VariadicSetterFunctions<Persistence::Data, void, T, InputPort&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  static const SetterFunctions<T>& getSetterFunctions()
  {
    static SetterFunctions<T> setterFunctions = createSetterFunctions<typename MCF::Data::VariadicSetterFunctions<Persistence::Data, void, T, InputPort&>, T, Setter>();
    return setterFunctions;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<bool, std::string> { static void execute(bool /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'bool' value to 'string' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<int, std::string> { static void execute(int /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'int' value to 'string' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<unsigned int, std::string> { static void execute(unsigned int /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'unsigned int' value to 'string' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<float, std::string> { static void execute(float /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'float' value to 'string' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<std::string, bool> { static void execute(std::string /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'string' value to 'bool' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<std::string, int> { static void execute(std::string /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'string' value to 'int' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<std::string, unsigned int> { static void execute(std::string /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'string' value to 'unsigned int' port"); } };

  //------------------------------------------------------------------------------------------------
  template <>
  struct Setter<std::string, float> { static void execute(std::string /*from*/, InputPort& /*port*/) { LOG_ERROR("Invalid Port Setter: 'string' value to 'float' port"); } };
}