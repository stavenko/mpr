#pragma once
#include <utility>
#include <unordered_map>
#include <string>

namespace mpr{
  typedef std::unordered_map<std::string, std::string> StringStringMap;
  std::pair<StringStringMap, StringStringMap> parseShader(std::string);
}
