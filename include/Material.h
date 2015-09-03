#pragma once
#include "interfaces/RenderSystem.hpp"
#include "shader_utils.h"
#include <memory>

namespace mpr{
  class Material final {
    // Responsibility:
    // Create and store material for opengl system,
    // Dispose material when none of shared_ptrs left.
    // Available to hold all info about material;
    typedef std::unordered_map<std::string, std::string>  SSMap;
    private:
      unsigned int programId;
      std::unordered_map<std::string, unsigned int> uniformLocations;
      std::unordered_map<std::string, unsigned int> attributeLocations;
      SSMap shaderAttributeTypes;
      SSMap shaderUniformTypes;
    private:
      Material();
      Material(Material &m);
      Material &operator=(Material &m);
      void disposeMaterial() {
        std::cout << "You have forget to dispose material\n"; 
      }
    public:
      Material(std::weak_ptr<RenderSystem> r, 
               std::string vertexShader, 
               std::string fragmentShader){
        std::pair<SSMap, SSMap> vsResult = parseShader(vertexShader);
        std::pair<SSMap, SSMap> fsResult = parseShader(fragmentShader);
        for(auto p: vsResult.first){
          shaderAttributeTypes.insert(p);
        }
        for (auto p: vsResult.second){
          shaderUniformTypes.insert(p);
        }

        for(auto p: fsResult.first){
          shaderAttributeTypes.insert(p);
        }
        for (auto p: fsResult.second){
          shaderUniformTypes.insert(p);
        }
      };
      ~Material(){
        this->disposeMaterial();
      }
      SSMap getUniformTypes(){ return shaderUniformTypes; }
      SSMap getAttributeTypes(){ return shaderAttributeTypes; }
  };
}
