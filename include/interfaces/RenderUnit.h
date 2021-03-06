#pragma once

#include "attribute_provider.h"
#include "uniform_provider.h"
#include "material_provider.h"
#include "../common/utils.hpp"

namespace mpr {
using ::std::unordered_map;
using ::std::string;
using ::std::weak_ptr;
using ::std::shared_ptr;
using ::std::pair;
using ::std::vector;
class RenderUnit final : public MaterialProvider,
                         public UniformProvider,
                         public AttributeProvider {

  RenderUnit() {};

 public:
  RenderUnit(RenderUnit const &other) {
    this->uniforms = other.uniforms;
    this->material = other.material;
    this->attributes = other.attributes;
    this->passName = other.passName;
    this->drawPoints = other.drawPoints;
    this->drawType = other.drawType;
  }
  RenderUnit(std::shared_ptr<Material> m, Uniforms u, Attributes a,
             std::string passName)
      : uniforms(u), attributes(a), material(m), passName(passName) {
    std::cout << "render unit created.\n";
  }
  virtual ~RenderUnit() {}
  string getPassName() { return this->passName; }

 private:
  Uniforms uniforms;
  Attributes attributes;
  shared_ptr<Material> material;
  string passName;
  uint16_t drawType;
  uint32_t drawPoints;

 public:  // implementations;
  virtual shared_ptr<Material> getMaterial() { return material; }
  virtual const unordered_map<string, unsigned int> &getAttributeLocations() {
    return material->getAttributeLocations();
  }
  virtual const unordered_map<string, unsigned int> &getUniformLocations() {
    return material->getUniformLocations();
  }
  virtual vector<string> uniformNames() { return keys(uniforms); }
  virtual shared_ptr<Uniform> getUniformValue(string name) {
    return uniforms[name];
  }
  virtual const Uniforms allUniforms() { return uniforms; }
  virtual vector<string> attributeNames() { return keys(attributes); }
  virtual shared_ptr<Attribute> getAttributeLocation(string attributeName) {
    return attributes[attributeName];
  }
  virtual const Attributes allAttributes() { return attributes; }
  virtual void install(const string key, const shared_ptr<Attribute> a) {
    attributes.emplace(key, a);
  }
  virtual void setAttributesDrawType(uint16_t t){ drawType = t;}
  virtual uint16_t getAttributesDrawType(){ return drawType;}
  virtual void setAttributePointAmount(uint32_t f){ drawPoints = f; } 
  virtual uint32_t getAttributePointAmount(){ 
    return  drawPoints ;
  }

  virtual const boost::optional<std::shared_ptr<Attribute>> findAttribute(
      const string key) {
    auto it = attributes.find(key);
    if (it == attributes.end())
      return boost::optional<std::shared_ptr<Attribute>>();
    else
      return boost::optional<std::shared_ptr<Attribute>>(it->second);
  }

  virtual const boost::optional<std::shared_ptr<Uniform>> findUniform(
      const string key) {
    auto it = uniforms.find(key);
    if (it == uniforms.end())
      return boost::optional<std::shared_ptr<Uniform>>();
    else
      return boost::optional<std::shared_ptr<Uniform>>(it->second);
  }
};
}
