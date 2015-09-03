#pragma once
#include <unordered_map>
#include <string>

namespace mpr{
  class RenderSystem {
    public:
      RenderSystem() {
        std::cout << "Render System initialized" << "\n";
      }
      virtual ~RenderSystem() {} ;
      virtual void finalizeRenderLoop() = 0;
  };
}
