#include "ContextRenderer.hpp"
#include "interfaces/RenderUnit.h"

namespace mpr {
using std::shared_ptr;
void ContextRenderer::finishRender(uint16_t type, uint32_t amount) {
  this->renderSystem->render(type, amount);


  
}
void ContextRenderer::setAttributes(shared_ptr<Material> m,
                                    shared_ptr<AttributeProvider> r) {
  for (auto attr : m->getAttributeLocations()) {
    auto maybeAttribute = r->findAttribute(attr.first);
    if (maybeAttribute)
      maybeAttribute.get()->set(this->renderSystem, attr.second);
    else
      std::cout << "Didn't found attribute, search it in scene: " << attr.first
                << "\n";
  }
}

void ContextRenderer::setUniforms(shared_ptr<Material> m,
                                  shared_ptr<UniformProvider> const r) {
  for (auto uni : m->getUniformLocations()) {
    auto maybeUniform = r->findUniform(uni.first);
    if (maybeUniform)
      maybeUniform.get()->set(this->renderSystem, uni.second);
    else
      std::cout << "uniform not found, search elsewhere: " << uni.first << "\n";
  }
}

void ContextRenderer::setMaterial(std::shared_ptr<MaterialProvider> r) {
  r->getMaterial()->set();
  // std::cout << "set material:" << r->getMaterial() << "\n";
}

void ContextRenderer::preparePass(Pass &p) {
  // std::cout << "prepare pass:" << p.name << "\n";
  renderSystem->startRender();
}

void ContextRenderer::unitRender(shared_ptr<RenderUnit> r) {
  this->setMaterial(r);
  this->setUniforms(r->getMaterial(), r);
  auto attrProvider = static_cast<shared_ptr<mpr::AttributeProvider>>(r);
  this->setAttributes(r->getMaterial(), attrProvider);
  this->finishRender(attrProvider->getAttributesDrawType(), 
      attrProvider->getAttributePointAmount());
}

void ContextRenderer::renderPass(Context const &ctx, Pass &p) {
  this->preparePass(p);
  for (auto ru : ctx.getRenderUnits(p.name)) {
    this->unitRender(ru);
  }

}

void ContextRenderer::render(Context const &ctx) {
  this->renderSystem->viewport();

  for (auto pass : ctx.getPasses()) {
    this->renderPass(ctx, pass);
  }
  this->renderSystem->finalizeRenderLoop();
}
}
