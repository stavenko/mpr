#include <iostream>
namespace mpr{
  class Attribute final{
    Attribute();
    Attribute &operator=(Attribute&);

    public:
      explicit Attribute(std::weak_ptr<RendererInitializer> r, 
        char *bufferData
      ) {
        std::cout << "create buffer\n";
      }
      ~Buffer(){
        std::cout << "Dispose buffer\n";
      }
      unsigned int getBufferId(){
        return -1;
      }
  }
}

