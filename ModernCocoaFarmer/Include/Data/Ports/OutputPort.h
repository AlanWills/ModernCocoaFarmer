#pragma once

#include "Data/Ports/InputPort.h"
#include "Persistence/Data.h"
#include "Assert/Assert.h"

#include <vector>


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  template <typename VariantType, typename ReturnType, typename... Args>
  struct Functions
  {
    using Variant = VariantType;
    using Function = ReturnType(*)(Args...);

    constexpr size_t size() const { return std::variant_size<Variant>::value; }

    Function m_functions[std::variant_size<Variant>::value];
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, size_t index, typename From, template <typename, typename> class Functor>
  struct SetVariantFunction
  {
    static constexpr void set(VariantFunctions& variantFunctions)
    {
      variantFunctions.m_functions[index] = &Functor<From, typename std::variant_alternative<index, typename VariantFunctions::Variant>::type>::execute;
      SetVariantFunction<VariantFunctions, index - 1, From, Functor>::set(variantFunctions);
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, typename From, template <typename, typename> class Functor>
  struct SetVariantFunction<VariantFunctions, 0, From, Functor>
  {
    static constexpr void set(VariantFunctions& variantFunctions)
    {
      variantFunctions.m_functions[0] = &Functor<From, typename std::variant_alternative<0, typename VariantFunctions::Variant>::type>::execute;
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, typename From, template <typename, typename> class Functor>
  constexpr VariantFunctions createVariantFunctions()
  {
    VariantFunctions variantFunctions = VariantFunctions();
    SetVariantFunction<VariantFunctions, variantFunctions.size() - 1, From, Functor>::set(variantFunctions);

    return variantFunctions;
  }

  template <typename From, typename To>
  struct Setter
  {
    static void execute(From from, Port& port)
    {
      static_cast<InputPort<To>&>(port).setValue(static_cast<To>(from));
    }
  };

  template <typename From>
  struct Setter<From, std::string>
  {
    static void execute(From /*from*/, Port& /*port*/)
    {
    }
  };

  template <typename T>
  class OutputPort : public Port
  {
    public:
      OutputPort(const std::string& name);

      size_t getType() const override { return celstl::variant_index<Persistence::Data, T>(); }
      void setValue(T newValue);
      void connect(Port& port) { m_outputs.push_back(&port); }

    private:
      using SetterFunctions = celstl::VariantFunctions<Persistence::Data, void, T, Port&>;

      static SetterFunctions m_setterFunctions;

      std::vector<observer_ptr<Port>> m_outputs;
  };

  template <typename T>
  typename OutputPort<T>::SetterFunctions OutputPort<T>::m_setterFunctions = createVariantFunctions<typename OutputPort<T>::SetterFunctions, T, Setter>();

  template <typename T>
  OutputPort<T>::OutputPort(const std::string& name)
    : Port(name)
  {
  }

  template <typename T>
  void OutputPort<T>::setValue(T newValue)
  {
    for (const auto& port : m_outputs)
    {
      size_t portType = port->getType();
      ASSERT(portType < m_setterFunctions.size());

      if (portType < m_setterFunctions.size())
      {
        m_setterFunctions.m_functions[portType](newValue, *port);
      }
    }
  }
}