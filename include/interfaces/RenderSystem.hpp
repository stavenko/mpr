#pragma once
#include <unordered_map>
#include <string>

namespace mpr{
  class RenderSystem {
    public:
      RenderSystem() {}
      virtual ~RenderSystem() {} ;
      virtual void finalizeRenderLoop() = 0;
      virtual unsigned int createProgram(const std::string, 
                                         const std::string) = 0;
      virtual void disposeProgram(unsigned int const) = 0;
  };
}
