#pragma once
#include "interfaces/RendererInitializer.hpp"
#include <memory>

namespace mpr{
  class Material final{
    private:
      unsigned int programId;
      std::unordered_map<std::string, unsigned int> uniformLocations;
      std::unordered_map<std::string, unsigned int> attributeLocations;
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
  };
}
