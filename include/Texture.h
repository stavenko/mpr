#include <iostream>
namespace mpr{
  class Texture final{
    Texture();
    Texture &operator=(Texture&)

    public:
      explicit Texture(std::weak_ptr<RendererInitializer> r, char *textureData){
        std::cout << "create texture\n";
      }
      ~Texture(){
        std::cout << "Dispose texture\n";
      }
      unsigned int getTextureId(){
        return -1;
      }
  }
}
