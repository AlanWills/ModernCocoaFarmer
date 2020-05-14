#include "Debug/Windows/DataSystemDolceWindow.h"
#include "Persistence/DataSystem.h"

#include "imgui/imgui_stdlib.h"


namespace MCF::Debug
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::DataStore::Data;

  template <class VariantType, typename ReturnType, typename... Args>
  struct VariantFunctions
  {
    using Variant = VariantType;
    using Function = ReturnType(*)(Args...);

    constexpr size_t size() const { return std::variant_size<Data>::value; }

    Function m_functions[std::variant_size<Data>::value];
  };

  using RenderFunctions = VariantFunctions<Data, void, const std::string&, const Data&, Persistence::DataStore&>;

  bool render(const std::string& key, bool& value)
  {
    return ImGui::Checkbox(key.c_str(), &value);
  }

  bool render(const std::string& key, int& value)
  {
    return ImGui::InputInt(key.c_str(), &value);
  }

  bool render(const std::string& key, unsigned int& value)
  {
    int iValue = static_cast<int>(value);
    if (ImGui::InputInt(key.c_str(), &iValue))
    {
      value = static_cast<unsigned int>(iValue);
      return true;
    }

    return false;
  }

  bool render(const std::string& key, float& value)
  {
    return ImGui::InputFloat(key.c_str(), &value);
  }

  bool render(const std::string& key, std::string& value)
  {
    return ImGui::InputText(key.c_str(), &value);
  }

  template <typename T>
  struct RenderFunctor
  {
    static void execute(const std::string& key, const Data& data, Persistence::DataStore& dataStore)
    {
      T tempData = std::get<T>(data);

      if (render(key, tempData))
      {
        dataStore.set(key, tempData);
      }
    }
  };

  template <typename VariantFunctions, size_t index>
  struct SetVariantFunction
  {
    static constexpr void _(VariantFunctions& renderFunctions)
    {
      renderFunctions.m_functions[index] = &RenderFunctor<typename std::variant_alternative<index, typename VariantFunctions::Variant>::type>::execute;
      SetVariantFunction<VariantFunctions, index - 1>::_(renderFunctions);
    }
  };

  template <typename VariantFunctions>
  struct SetVariantFunction<VariantFunctions, 0>
  {
    static constexpr void _(VariantFunctions& renderFunctions)
    {
      renderFunctions.m_functions[0] = &RenderFunctor<typename std::variant_alternative<0, typename VariantFunctions::Variant>::type>::execute;
    }
  };

  template <typename VariantFunctions>
  constexpr VariantFunctions createVariantFunctions()
  {
    VariantFunctions variantFunctions = VariantFunctions();
    SetVariantFunction<VariantFunctions, variantFunctions.size() - 1>::_(variantFunctions);

    return variantFunctions;
  }

  static RenderFunctions s_renderFunctions = createVariantFunctions<RenderFunctions>();

  //------------------------------------------------------------------------------------------------
  DataSystemDolceWindow::DataSystemDolceWindow(Persistence::DataSystem& dataSystem) :
    Inherited("Data System"),
    m_dataSystem(dataSystem)
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataSystemDolceWindow::render()
  {
    for (const auto& keyData : m_dataSystem.getDataStore_DebugOnly())
    {
      s_renderFunctions.m_functions[keyData.second.index()](keyData.first, keyData.second, m_dataSystem);
    }
  }
}