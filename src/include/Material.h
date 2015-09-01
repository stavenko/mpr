#pragma once
#include "interfaces/RendererInitializer.hpp"
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
        std::cout << "You have forget to disposeMaterial\n"; 
      }
    public:
      Material(std::weak_ptr<RendererInitializer> r, 
               std::string vertexShader, 
               std::string fragmentShader){
        std::cout << "Material is created.\n";
      };
      ~Material(){
        this->disposeMaterial();
      }
      SSMap getUniformTypes(){ return shaderUniformTypes; }
      SSMap getAttrubuteTypes(){ return shaderAttributeTypes; }
  };
}
