#pragma once
#include "attribute_provider.h"
#include "uniform_provider.h"
#include "material_provider.h"
#include "../common/utils.hpp"

namespace mpr{
  class RenderUnit final:
    public MaterialProvider, 
    public UniformProvider, 
    public AttributeProvider{
    RenderUnit(){};
    public:
      RenderUnit(RenderUnit const &other){
        this->uniforms = other.uniforms;
        this->material = other.material;
        this->attributes = other.attributes;
        this->passName = other.passName;

      }
      RenderUnit(std::shared_ptr<Material> m,
                 Uniforms u,
                 Attributes a,
                 std::string passName):
        uniforms(u),
        attributes(a),
        material(m),
        passName(passName)
      {
          std::cout << "render unit created.\n";
        }
      virtual ~RenderUnit(){}
      std::string getPassName() { return this->passName; }

    private:
      Uniforms uniforms;
      Attributes attributes;
      std::shared_ptr<Material> material;
      std::string passName;
    public: // implementations;
      virtual std::shared_ptr<Material> getMaterial(){ return material;}
      virtual std::unordered_map<string, uint16_t> getLocations(){ return material.getLocations();}
      virtual std::vector<std::string> uniformNames(){ return keys(uniforms);}
      virtual std::shared_ptr<Uniform> getUniformValue(std::string name){
        return uniforms[name];
      }
      virtual const Uniforms allUniforms(){
        return uniforms;
      }
      virtual std::vector<std::string> attributeNames() {
        return keys(attributes);
      }
      virtual std::shared_ptr<Attribute> getAttributeLocation(std::string attributeName){
        return attributes[attributeName];
      }
      virtual const Attributes allAttributes(){
        return attributes;
      }
      virtual void set(const std::string key, const std::shared_ptr<Attribute> a) {
        attributes.emplace(key, a);
      } 
  };
}
