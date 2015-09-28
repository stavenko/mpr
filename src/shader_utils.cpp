
#include "../include/shader_utils.h"
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <boost/algorithm/string.hpp>
namespace mpr{
  std::regex getUniformRegex(int){
    return std::regex("^uniform (\\w+) (\\w+);"); 
  }

  std::regex getAttributeRegex(int version){
    if(version >= 330 ) 
      return std::regex("^layout(.*)\\s+in\\s+(\\w+)\\s+(\\w+);");
    return std::regex("^attribute\\s+(\\w+)\\s+(\\w+);");
  }

  std::pair<StringStringMap, StringStringMap> 
    parseShader(std::string shader){
      std::vector<std::string> lines;
      boost::split(lines, shader, boost::is_any_of("\n"));
      std::string firstLine = lines[0];
      std::smatch m;
      std::regex r("\\d+");
      std::regex_search(firstLine, m, r);
      int version;
      std::stringstream(m[0]) >> version;
      std::regex uniformRegex = getUniformRegex(version),
                 attributeRegex = getAttributeRegex(version);
      StringStringMap uniforms, attributes;
      
      for(auto &line :lines){
        std::smatch umatch;
        std::cout << "L:" <<  line <<   "\n";
        std::regex_match(line, umatch, uniformRegex);
        if(umatch.size() > 0)
          uniforms.insert(std::make_pair(umatch[2], umatch[1]));
        std::smatch amatch;
        std::regex_match(line, amatch, attributeRegex);
        if(amatch.size() > 0)
          attributes.insert(std::make_pair(amatch[2], amatch[1]));
      }
    return std::make_pair(attributes, uniforms);
  }

}
