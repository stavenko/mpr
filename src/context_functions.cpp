#include "include/Context.h"
namespace mpr{
  void Context::add(Pass &p){
    passes.push_back(p);
  }
  void Context::add(std::shared_ptr<Renderable> r){
    std::cout << "Add Renderable to context\n";
    if(passes.size() == 0) {
      std::cout << "Cannot add object, Context has no any passes\n";
      return;
    }

    for(auto renderUnit :r->getUnits()){
      auto passOpts = std::find_if(passes.begin(), passes.end(), 
        [&renderUnit](Pass &p){
          return renderUnit.getPassName() == p.name;
        }
      );
      if(passOpts == passes.end()) {
        std::cout << "pass not found\n";
        continue;
      }
      std::cout << "pass\n";
      std::string name = renderUnit.getPassName();
      std::shared_ptr<RenderUnit> ruPtr(new RenderUnit(renderUnit));
      if(renderUnits.count(name) == 0){
        std::pair<std::string, RenderUnits> pair =
          std::make_pair(name, RenderUnits());
        renderUnits.insert(pair);
      }
      renderUnits[name].push_back(ruPtr);
    }
  }
  void Context::setUniforms(std::shared_ptr<UniformProvider> r) {
    std::cout << "set setUniforms:" << "\n";
  }

  void Context::finishRender(){
    std::cout << "Finish rendering\n";
  }
  void Context::setAttributes(std::shared_ptr<AttributeProvider> r){
    std::cout << "setAttributes\n";
  }

  void Context::setMaterial(std::shared_ptr<MaterialProvider> r) {
    std::cout << "set material:" << r->getMaterial() << "\n";
  }

  void Context::preparePass(Pass &p){
    std::cout << "prepare pass:" << p.name << "\n";
  }

  void Context::unitRender(std::shared_ptr<RenderUnit> r) {
    this->setMaterial(r);
    this->setAttributes(static_cast<std::shared_ptr<mpr::AttributeProvider>>(r));
    this->setUniforms(r);
    this->finishRender();
  }

  void Context::renderPass(Pass &p){
    this->preparePass(p);
    for(auto ru : this->renderUnits[p.name]){
      this->unitRender(ru); 
    }
  }

  void Context::render() {
    std::cout << "render\n";
    for(auto pass : passes) {
      this->renderPass(pass); 
    }
  }
}
