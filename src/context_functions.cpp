#include "ContextRenderer.hpp"
#include "interfaces/RenderUnit.h"

namespace mpr{
  void ContextRenderer::finishRender(){
    // std::cout << "Finish rendering\n";
  }
  void ContextRenderer::setAttributes(std::shared_ptr<AttributeProvider> r){
    // std::cout << "setAttributes\n";
  }

  void ContextRenderer::setMaterial(std::shared_ptr<MaterialProvider> r) {
    // std::cout << "set material:" << r->getMaterial() << "\n";
  }

  void ContextRenderer::preparePass(Pass &p){
    // std::cout << "prepare pass:" << p.name << "\n";
  }

  void ContextRenderer::unitRender(std::shared_ptr<RenderUnit> r) {
    this->setMaterial(r);
    this->setAttributes(static_cast<std::shared_ptr<mpr::AttributeProvider>>(r));
    this->setUniforms(r);
    this->finishRender();
  }

  void ContextRenderer::renderPass(Context const &ctx, Pass &p){
    this->preparePass(p);
    for(auto ru : ctx.getRenderUnits(p.name)){
      this->unitRender(ru); 
    }
  }
  void ContextRenderer::setUniforms(std::shared_ptr<UniformProvider> const r) {
    // std::cout << "set setUniforms:" << "\n";
  }

  void ContextRenderer::render(Context const &ctx) {
    // std::cout << "render\n";
    
    for(auto pass : ctx.getPasses()) {
      this->renderPass(ctx, pass); 
    }
    this->renderSystem->finalizeRenderLoop();
    // std:: cout << "REnder finished\n";
  }
}
