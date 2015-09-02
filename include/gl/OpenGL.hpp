#include "../interfaces/RenderSystem.hpp"

namespace mpr{
  class OpenGL final :public RenderSystem{
    public:
      OpenGL() {
        std::cout << "init opengl\n";
      }
      virtual ~OpenGL(){
        std::cout << "close opengl\n";
      }
  };
}
