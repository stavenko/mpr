#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "interfaces/RenderSystem.hpp"
namespace mpr{
  class Attribute final{
    // Thread unsafe!!!
    Attribute();
    Attribute &operator=(Attribute&);
    unsigned int bufferId;
    std::weak_ptr<RenderSystem> renderer;

    public:
      template<typename T>
      explicit Attribute(
        std::weak_ptr<RenderSystem> r, 
        std::vector<T> &input
      ):bufferId(-1), renderer(r){
        std::shared_ptr<RenderSystem> rs(r);
        bufferId = rs->createBuffer(sizeof(input), &input[0][0]);
      }
      ~Attribute(){
        std::cout << "Dispose buffer\n";
        std::shared_ptr<RenderSystem> rs(renderer);
        rs->deleteBuffer(bufferId);
      }
      unsigned int getBufferId(){
        return bufferId;
      }
  };
  typedef std::unordered_map<std::string, std::shared_ptr<Attribute>> Attributes;
}

