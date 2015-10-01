#pragma once
#include "interfaces/RenderSystem.hpp"
#include "shader_utils.h"
#include <memory>
#include <string>
#include <iostream>

namespace mpr{
  using ::std::unordered_map;
  using ::std::string;
  using ::std::weak_ptr;
  using ::std::shared_ptr;
  using ::std::pair;
  class Material final {

    // Responsibility:
    // Create and store material for opengl system,
    // Dispose material when none of shared_ptrs left.
    // Available to hold all info about material;
    typedef unordered_map<string, string>  SSMap;
    private:
      weak_ptr<RenderSystem> renderSystem;
      unsigned int programId;
      unordered_map<string, unsigned int> uniformLocations;
      unordered_map<string, unsigned int> attributeLocations;
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
      void readInputs(const string vShader, const string fShader){
        pair<SSMap, SSMap> vsResult = parseShader(vShader);
        pair<SSMap, SSMap> fsResult = parseShader(fShader);
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
      
      void compileProgram(const string vShader, const string fShader){
        shared_ptr<RenderSystem> rs(renderSystem);
        programId = rs->createProgram(vShader, fShader);
        for(auto &uni: shaderUniformTypes)
          uniformLocations.emplace(uni.first, 
              rs->getUniformLocation(programId, uni.second));
        for(auto &attr:shaderAttributeTypes)
          attributeLocations.emplace(attr.first,
            rs->getAttributeLocation(programId, attr.second));
      }
    public:
      Material(weak_ptr<RenderSystem> r, 
               const string vertexShader, 
               const string fragmentShader):renderSystem(r){
        readInputs(vertexShader, fragmentShader);
        compileProgram(vertexShader, fragmentShader);
      };
      ~Material(){
        this->disposeMaterial();
      }
      const unordered_map<string, unsigned int> &
        getAttributeLocations(){ return attributeLocations; }
      const unordered_map<string, unsigned int> &
        getUniformLocations(){ return uniformLocations; }

      const SSMap getUniformTypes(){ return shaderUniformTypes; }
      const SSMap getAttributeTypes(){ return shaderAttributeTypes; }
  };
}
