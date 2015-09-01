#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "interfaces/RendererInitializer.hpp"
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
      ~Attribute(){
        std::cout << "Dispose buffer\n";
      }
      unsigned int getBufferId(){
        return -1;
      }
  };
  typedef std::unordered_map<std::string, std::shared_ptr<Attribute>> Attributes;
}

