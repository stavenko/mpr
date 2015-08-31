#pragma once
#include <unordered_map>
#include <string>

namespace mpr{
  class RendererInitializer {
    public:
      RendererInitializer() {
        std::cout << "Renderer initialized" << "\n";
      }
  };
}
