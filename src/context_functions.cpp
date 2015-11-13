#include "ContextRenderer.hpp"
#include "interfaces/RenderUnit.h"

namespace mpr{
  using std::shared_ptr;
  void ContextRenderer::finishRender(){
    // std::cout << "Finish rendering\n";
  }
  void ContextRenderer::setAttributes(
      shared_ptr<Material> m ,
      shared_ptr<AttributeProvider> r)
  {
    for(auto attr:m->getAttributeLocations()){
      auto attribute = r->getAttributeLocation(attr.first);
      std::cout << "ATTR:" << attribute->getBufferId() << " " << attr.second << "\n";

      
    }
  }

  void ContextRenderer::setUniforms(
      shared_ptr<Material> m,
      shared_ptr<UniformProvider> const r) 
  {
    for(auto uni:m->getUniformLocations()){
      // std::cout << uni.first << " " << uni.second << "\n";
    }
  }

  void ContextRenderer::setMaterial(std::shared_ptr<MaterialProvider> r) {
    // std::cout << "set material:" << r->getMaterial() << "\n";
  }

  void ContextRenderer::preparePass(Pass &p){
    // std::cout << "prepare pass:" << p.name << "\n";
  }

  void ContextRenderer::unitRender(shared_ptr<RenderUnit> r) {
    this->setMaterial(r);
    this->setAttributes(r->getMaterial(),static_cast<shared_ptr<mpr::AttributeProvider>>(r));
    this->setUniforms(r->getMaterial(), r);
    this->finishRender();
  }

  void ContextRenderer::renderPass(Context const &ctx, Pass &p){
    this->preparePass(p);
    for(auto ru : ctx.getRenderUnits(p.name)){
      this->unitRender(ru); 
    }
  }

  void ContextRenderer::render(Context const &ctx) {
    // std::cout << "render\n";
    this->renderSystem->viewport();
    
    
    for(auto pass : ctx.getPasses()) {
      this->renderPass(ctx, pass); 
    }
    this->renderSystem->finalizeRenderLoop();
    // std:: cout << "REnder finished\n";
  }
}
