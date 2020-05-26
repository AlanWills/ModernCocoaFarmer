#pragma once

#include "Data/Ports/InputPort.h"
#include "CelesteStl/Templates/Variant.h"
#include "CelesteStl/Templates/Unused.h"


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
  struct TypedSetter
  {
    static void execute(From from, InputPort& port)
    {
      if constexpr (std::is_convertible<From, To>::value)
      {
        port.setValue(static_cast<To>(from));
      }
      else
      {
        celstl::unused(from);
        celstl::unused(port);
      }
    }
  };

  //------------------------------------------------------------------------------------------------
  template <>
  struct TypedSetter<std::string, std::string>
  { 
    static void execute(std::string from, InputPort& port) 
    { 
      port.setValue(from);
    } 
  };

  //------------------------------------------------------------------------------------------------
  template <typename TData>
  struct TypelessSetter
  {
    static void execute(const Persistence::Data& data, InputPort& port)
    {
      port.setValue<TData>(std::get<TData>(data));
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename From>
  using TypedSetterFunctions = MCF::Data::VariadicSetterFunctions<Persistence::Data, void, From, InputPort&>;

  //------------------------------------------------------------------------------------------------
  using TypelessSetterFunctions = celstl::VariantFunctions<Persistence::Data, void, const Persistence::Data&, InputPort&>;

  //------------------------------------------------------------------------------------------------
  template <typename From>
  static const TypedSetterFunctions<From>& getSetterFunctions()
  {
    static TypedSetterFunctions<From> setterFunctions = createSetterFunctions<typename MCF::Data::VariadicSetterFunctions<Persistence::Data, void, From, InputPort&>, From, TypedSetter>();
    return setterFunctions;
  }

  //------------------------------------------------------------------------------------------------
  const TypelessSetterFunctions& getSetterFunctions();
}