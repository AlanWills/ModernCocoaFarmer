#pragma once

#include <unordered_map>
#include <string>


namespace CelesteEngine
{
  class Path;
}

namespace MCF
{
  namespace Persistence
  {
    class LocalData
    {
      public:
        LocalData();
        ~LocalData();
        LocalData(const LocalData&) = delete;
        LocalData& operator=(const LocalData&) = delete;

        bool hasData(const std::string& dataKey) const;
        
        template <typename T>
        T getData(const std::string& dataKey) const;

        template <typename T>
        void setData(const std::string& dataKey, T data);

        void load(const CelesteEngine::Path& filePath);
        void save(const CelesteEngine::Path& filePath);

      private:
        enum class DataType
        {
          kInt,
          kFloat,
          kString
        };

        struct Data
        {
          DataType m_dataType;

          union
          {
            int m_int;
            float m_float;
            const char* m_string;
          } m_data;
        };

        std::unordered_map<std::string, Data> m_dataLookup;
    };
  }
}