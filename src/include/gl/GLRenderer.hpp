#include "../interfaces/RendererInitializer.hpp"

namespace mpr{
  class OpenGLRenderer final :public RendererInitializer{
    public:
      OpenGLRenderer() {
        std::cout << "init opengl\n";
      }
      virtual ~OpenGLRenderer(){
        std::cout << "close opengl\n";
      }
  };
}
