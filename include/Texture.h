#include <iostream>
#include <IL/il.h>
#include <IL/ilu.h>
namespace mpr {
class Texture final {
  Texture();
  Texture &operator=(Texture &);

 public:
  explicit Texture(std::weak_ptr<RenderSystem> r, 
      unsigned char *data,  uint16_t inputType,
      uint16_t width, uint16_t height ) {
  }
  ~Texture() { std::cout << "Dispose texture\n"; }
  unsigned int getTextureId() { return -1; }
};
}
