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
      Context &operator=(Context &ctx);
    public:
      void add(Pass const &p){
        passes.push_back(p);
      }
      void add(std::shared_ptr<Renderable> const r){
        std::cout << "Add Renderable to context\n";
        if(passes.size() == 0) {
          std::cout << "Cannot add object, ContextRenderer has no any passes\n";
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
      void setUniforms(std::shared_ptr<UniformProvider> r) {
        std::cout << "set setUniforms:" << "\n";
      }
      std::vector<Pass> const getPasses() const { return passes; }
      std::vector<RenderUnitPtr> 
        getRenderUnits(std::string forPass) const { 
        return renderUnits.at(forPass);
      }
      Context(){}
      Context(Context const &ctx){
        this->uniforms = ctx.uniforms;
        this->passes = ctx.passes;
        this->renderUnits = ctx.renderUnits;
      }
      void remove(std::shared_ptr<Renderable> r);

      virtual std::vector<std::string> uniformNames(){
        return keys(uniforms);
      }

      virtual std::shared_ptr<Uniform> getUniformValue(std::string uniformName){
        return uniforms[uniformName];
      }
      virtual const Uniforms allUniforms(){ return uniforms;}

  };


}


