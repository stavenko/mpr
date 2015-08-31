#pragma once
#include "common/Attribute.h"
#include "Material.h"
#include "common/utils.hpp"

namespace mpr{
  class RenderablePass final:public UniformProvider, public AttributeProvider {
    typedef std::unordered_map<std::string, std::shared_ptr<Attribute>> Attributes;
    typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
    std::shared_ptr<Material> material;
    std::string name;
    Uniforms uniforms;
    Attributes attributes;

    private:
      RenderablePass(){};
    public:
      RenderablePass(RenderablePass &rp):
        material(rp.material),
        name(rp.name),
        uniforms(rp.uniforms),
        attributes(rp.attributes){}
      RenderablePass(std::shared_ptr<Material> m,
                     std::string name):
      material(m),
      name(name){}
      std::string getName(){
      return name;
    }


    public:
      virtual std::vector<std::string> uniformNames() {
        return keys(uniforms);
      }
      virtual std::shared_ptr<Uniform> getUniformValue(std::string uniformName){
        return uniforms[uniformName];
      }

      virtual std::vector<std::string> attributeNames() {
        return keys(attributes);
      }
      virtual std::shared_ptr<Attribute> getAttributeLocation(std::string attributeName){
        return attributes[attributeName];
      }
      virtual std::shared_ptr<Material> getMaterial(){
        return material;
      }
  };
}
