#include <string>
#include <boost/filesystem.hpp>
#include <CImg.h>
#include <iostream>
#include "./interfaces/RenderSystem.hpp"

namespace mpr {
class Texture final {
  Texture();
  Texture &operator=(Texture &);

 public:
  explicit Texture(std::weak_ptr<RenderSystem> r, std::string fileName) {
    boost::filesystem::path file(fileName);
    std::string ext = file.extension().string();
    std::cout << "Extension: " << ext << "\n";
    if(ext == ".jpg")
      std::cout << "read jpeg\n";
    
  }
  ~Texture() { std::cout << "Dispose texture\n"; }
  unsigned int getTextureId() { return -1; }
};
}
