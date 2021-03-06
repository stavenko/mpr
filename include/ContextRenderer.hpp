#pragma once
#include <memory>
#include <iostream>
#include "interfaces/RenderSystem.hpp"
#include "interfaces/RenderUnit.h"
#include "Pass.h"
#include "Context.h"


namespace mpr{
  class ContextRenderer final{
    private:
      ContextRenderer(){}
      std::shared_ptr<RenderSystem> renderSystem;
      unsigned int attributeArrayCount;
    public:
      ContextRenderer(std::shared_ptr<RenderSystem> renderSystem):
        renderSystem(renderSystem),
        attributeArrayCount(0)
    {}
    private:
      void unitRender(std::shared_ptr<RenderUnit>);
      void renderPass(Context const&, Pass&);
      void preparePass(Pass&);

      void setMaterial(std::shared_ptr<MaterialProvider>);
      void setAttributes(std::shared_ptr<Material>, std::shared_ptr<AttributeProvider>);
      void setUniforms(std::shared_ptr<Material>, std::shared_ptr<UniformProvider>);
      void finishRender(uint16_t, uint32_t);
    public:
      void render(Context const&);
      
  };
}
