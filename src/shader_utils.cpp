
#include "../include/shader_utils.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
namespace mpr{
  std::pair<StringStringMap, StringStringMap> 
    parseShader(std::string shader){
      std::vector<std::string> lines;
      boost::split(lines, shader, boost::is_any_of("\n"));
      for(auto line :lines){
        std::cout << "L:" << line << "\n";
      }

    return std::make_pair(StringStringMap(), StringStringMap());
  }
}
