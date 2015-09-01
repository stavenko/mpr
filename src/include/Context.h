#pragma once
#include <iostream>
#include "interfaces/uniform_provider.h"
#include "interfaces/Renderable.h"
#include "interfaces/RenderUnit.h"
#include "Pass.h"

namespace mpr{

  class Context:private UniformProvider{
    typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
    typedef std::shared_ptr<RenderUnit> RenderUnitPtr; 
    typedef std::vector<RenderUnitPtr> RenderUnits;
    private:
      Uniforms uniforms;
      std::vector<Pass> passes;
      std::unordered_map<
        std::string, 
        std::vector<RenderUnitPtr>
      > renderUnits;
    private:
      Context();
      Context(Context &ctx);
      Context &operator=(Context &ctx);
    public:
      explicit Context(std::weak_ptr<RenderSystem> r){}
      void add(std::shared_ptr<Renderable> r);
      void add(Pass&);
      void remove(std::shared_ptr<Renderable> r);
      void render();

      virtual std::vector<std::string> uniformNames(){
        return keys(uniforms);
      }

      virtual std::shared_ptr<Uniform> getUniformValue(std::string uniformName){
        return uniforms[uniformName];
      }
      virtual const Uniforms allUniforms(){ return uniforms;}
    private:
      void unitRender(std::shared_ptr<RenderUnit>);
      void renderPass(Pass&);
      void preparePass(Pass&);

      void setMaterial(std::shared_ptr<MaterialProvider>);
      void setAttributes(std::shared_ptr<AttributeProvider>);
      void setUniforms(std::shared_ptr<UniformProvider>);
      void finishRender();
  };


}


