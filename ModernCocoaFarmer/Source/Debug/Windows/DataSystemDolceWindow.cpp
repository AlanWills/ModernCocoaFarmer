#include "Debug/Windows/DataSystemDolceWindow.h"
#include "CelesteStl/Templates/Variant.h"
#include "Utils/StringUtils.h"
#include "Data/DataSystem.h"

#include "imgui/imgui_stdlib.h"
#include "imgui/DefaultInput.h"

#include <vector>


namespace MCF::Debug
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::Data;
  using InputFunctions = celstl::VariantFunctions<Data, void, const std::string&, const Data&, Persistence::DataStore&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct InputFunctor
  {
    static void execute(const std::string& key, const Data& data, Persistence::DataStore& dataStore)
    {
      T tempData = std::get<T>(data);

      if (Dolce::input(key.substr(key.find_last_of('.') + 1), tempData))
      {
        dataStore.set(key, tempData);
      }
    }
  };

  static InputFunctions s_inputFunctions = celstl::createVariantFunctions<InputFunctions, InputFunctor>();

  //------------------------------------------------------------------------------------------------
  DataSystemDolceWindow::DataSystemDolceWindow(MCF::Data::DataSystem& dataSystem) :
    Inherited("Data System"),
    m_dataSystem(dataSystem),
    m_dataSystemRoot()
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataSystemDolceWindow::render()
  {
    Dolce::input("Search", m_searchString);

    m_dataSystemRoot.m_children.clear();

    for (auto& keyData : m_dataSystem.getDataStore_DebugOnly())
    {
      size_t previousIndex = static_cast<size_t>(-1);
      size_t currentIndex = keyData.first.find('.');
      DataSystemNode* currentNode = &m_dataSystemRoot;

      while (currentIndex < keyData.first.size())
      {
        std::string key = keyData.first.substr(previousIndex + 1, currentIndex - (previousIndex + 1));
        if (currentNode->m_children.find(key) == currentNode->m_children.end())
        {
          ASSERT(currentNode->m_children.find(key) == currentNode->m_children.end());
          currentNode->m_children.emplace(key, DataSystemNode(key, currentNode, nullptr));
        }
        
        currentNode = &currentNode->m_children[key];
        previousIndex = currentIndex;
        currentIndex = keyData.first.find('.', previousIndex + 1);
      }

      std::string key = keyData.first.substr(previousIndex + 1);
      ASSERT(currentNode->m_children.find(key) == currentNode->m_children.end());
      currentNode->m_children.emplace(key, DataSystemNode(key, currentNode, &keyData.second));
    }
   
    std::vector<std::string> words;
    Celeste::split(m_searchString, words, '.');
    DataSystemNode* currentNode = &m_dataSystemRoot;

    for (const std::string& word : words)
    {
      if (currentNode->m_children.find(word) == currentNode->m_children.end())
      {
        break;
      }

      currentNode = &currentNode->m_children.at(word);
    }

    for (auto& children : currentNode->m_children)
    {
      renderNode(children.second);
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string DataSystemDolceWindow::getFullKey(const DataSystemNode& dataSystemNode)
  {
    std::vector<std::string> nodes;
    const DataSystemNode* current = &dataSystemNode;

    while (current != &m_dataSystemRoot)
    {
      nodes.push_back(current->m_relativeKey);
      current = current->m_parent;
    }

    std::string str;
    str.reserve(128);

    for (size_t i = nodes.size() - 1; i >= 1; --i)
    {
      str.append(nodes[i]);
      str.push_back('.');
    }
    str.append(nodes.front());

    return str;
  }

  //------------------------------------------------------------------------------------------------
  void DataSystemDolceWindow::renderNode(DataSystemNode& dataSystemNode)
  {
    if (dataSystemNode.m_children.empty())
    {
      ASSERT_NOT_NULL(dataSystemNode.m_data);
      s_inputFunctions.m_functions[dataSystemNode.m_data->index()](getFullKey(dataSystemNode), *dataSystemNode.m_data, m_dataSystem);
    }
    else
    {
      if (ImGui::TreeNode(dataSystemNode.m_relativeKey.c_str()))
      {
        for (auto& children : dataSystemNode.m_children)
        {
          renderNode(children.second);
        }

        ImGui::TreePop();
      }
    }
  }
}