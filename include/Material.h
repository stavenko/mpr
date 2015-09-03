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
      std::weak_ptr<RenderSystem> renderSystem;
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
        std::shared_ptr<RenderSystem> rs(renderSystem);
        rs->disposeProgram(programId);
      }
      void readInputs(const std::string vShader, const std::string fShader){
        std::pair<SSMap, SSMap> vsResult = parseShader(vShader);
        std::pair<SSMap, SSMap> fsResult = parseShader(fShader);
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
      }
      void compileProgram(const std::string vShader, const std::string fShader){
        std::shared_ptr<RenderSystem> rs(renderSystem);
        programId = rs->createProgram(vShader, fShader);
      }
    public:
      Material(std::weak_ptr<RenderSystem> r, 
               const std::string vertexShader, 
               const std::string fragmentShader):renderSystem(r){
        readInputs(vertexShader, fragmentShader);
        compileProgram(vertexShader, fragmentShader);
      };
      ~Material(){
        this->disposeMaterial();
      }
      const SSMap getUniformTypes(){ return shaderUniformTypes; }
      const SSMap getAttributeTypes(){ return shaderAttributeTypes; }
  };
}
