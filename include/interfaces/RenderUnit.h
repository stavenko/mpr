#pragma once
#include "attribute_provider.h"
#include "uniform_provider.h"
#include "material_provider.h"
#include "../common/utils.hpp"

namespace mpr{
    using ::std::unordered_map;
    using ::std::string;
    using ::std::weak_ptr;
    using ::std::shared_ptr;
    using ::std::pair;
    using ::std::vector;
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
      string getPassName() { return this->passName; }

    private:
      Uniforms uniforms;
      Attributes attributes;
      shared_ptr<Material> material;
      string passName;
    public: // implementations;
      virtual shared_ptr<Material> getMaterial(){ return material;}
      virtual const unordered_map<string, unsigned int> &getAttributeLocations(){ 
        return material->getAttributeLocations();
      }
      virtual const unordered_map<string, unsigned int> &getUniformLocations(){ 
        return material->getUniformLocations();
      }
      virtual vector<string> uniformNames(){ return keys(uniforms);}
      virtual shared_ptr<Uniform> getUniformValue(string name){
        return uniforms[name];
      }
      virtual const Uniforms allUniforms(){
        return uniforms;
      }
      virtual vector<string> attributeNames() {
        return keys(attributes);
      }
      virtual shared_ptr<Attribute> getAttributeLocation(string attributeName){
        return attributes[attributeName];
      }
      virtual const Attributes allAttributes(){
        return attributes;
      }
      virtual void set(const string key, const shared_ptr<Attribute> a) {
        attributes.emplace(key, a);
      } 
  };
}
