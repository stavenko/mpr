#include <iostream>
#include "interfaces/uniform_provider.h"
#include "interfaces/Renderable.h"
#include "interfaces/RenderUnit.h"

namespace mpr{

  class Context:private UniformProvider{
    typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
    
    private:
      Uniforms uniforms;
      std::vector<RenderablePass> passes;
      std::unordered_map<
        std::string, 
        std::vector<std::shared_ptr<RenderUnit>>
      > renderUnits;
    private:
      Context();
      Context(Context &ctx);
      Context &operator=(Context &ctx);
    public:
      explicit Context(std::weak_ptr<RendererInitializer> r){}
      void add(std::shared_ptr<Renderable> r);
      void remove(std::shared_ptr<Renderable> r);
      void render();

      virtual std::vector<std::string> uniformNames(){
        return keys(uniforms);
      }

      virtual std::shared_ptr<Uniform> getUniformValue(std::string uniformName){
        return uniforms[uniformName];
      }
    private:
      void unitRender(std::shared_ptr<RenderUnit>);
      void renderPass(RenderablePass&);
      void preparePass(RenderablePass&);

      void setMaterial(std::shared_ptr<MaterialProvider>);
      void setAttributes(std::shared_ptr<AttributeProvider>);
      void setUniforms(std::shared_ptr<UniformProvider>);
      void finishRender();
  };

  void Context::add(std::shared_ptr<Renderable> r){
    std::cout << "Add Renderable to context\n";
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

  void Context::preparePass(RenderablePass &rp){
    std::cout << "prepare pass:" << rp.getName() << "\n";
  }

  void Context::unitRender(std::shared_ptr<RenderUnit> r) {
    this->setMaterial(r);
    this->setAttributes(static_cast<std::shared_ptr<mpr::AttributeProvider>>(r));
    this->setUniforms(r);
    this->finishRender();
  }

  void Context::renderPass(RenderablePass &rp){
    this->preparePass(rp);
    for(auto ru : this->renderUnits[rp.getName()]){
      this->unitRender(ru); 
    }
  }

  void Context::render() {
    std::cout << "render\n";
    for(auto pass : passes) {
      this->renderPass(pass); 
    }
  }

  void finishRender(){
    std::cout << "Frame rendered.\n";
  }

}


