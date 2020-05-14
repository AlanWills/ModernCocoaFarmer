#include "Debug/Windows/DataSystemDolceWindow.h"
#include "Persistence/DataSystem.h"

#include "imgui/imgui_stdlib.h"


namespace MCF::Debug
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::DataStore::Data;
  using RenderFunction = void (*)(const std::string&, const Data&, Persistence::DataStore&);

  struct RenderFunctions
  {
    constexpr size_t size() const { return std::variant_size<Data>(); }

    RenderFunction m_functions[std::variant_size<Data>()];
  };

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
  void render(const std::string& key, const Data& data, Persistence::DataStore& dataStore)
  {
    T tempData = std::get<T>(data);

    if (render(key, tempData))
    {
      dataStore.set(key, tempData);
    }
  }

  template <size_t index>
  constexpr void setRenderFunction(RenderFunctions& renderFunctions)
  {
    renderFunctions.m_functions[index] = &render<typename std::variant_alternative<index, Data>::type>;
    setRenderFunction<index - 1>(renderFunctions);
  }

  template <>
  constexpr void setRenderFunction<0>(RenderFunctions& renderFunctions)
  {
    renderFunctions.m_functions[0] = &render<typename std::variant_alternative<0, Data>::type>;
  }

  constexpr RenderFunctions createRenderFunctions()
  {
    RenderFunctions renderFunctions = RenderFunctions();
    setRenderFunction<renderFunctions.size() - 1>(renderFunctions);

    return renderFunctions;
  }

  static RenderFunctions s_renderFunctions = createRenderFunctions();

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