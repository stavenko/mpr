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
    size_t size;
    uint16_t type;
    bool isNormalized;
    std::weak_ptr<RenderSystem> renderer;

    public:

      template<typename T>
      explicit Attribute(
        std::weak_ptr<RenderSystem> r, 
        std::vector<T> &input,
        bool in = false
      ):bufferId(-1), isNormalized(in), renderer(r){
        std::shared_ptr<RenderSystem> rs(r);
        bufferId = rs->createBuffer(sizeof(input), &input[0][0]);
        size = sizeof(T);
        type = rs->getItemType<T>();
      }

      void set(std::shared_ptr<RenderSystem> rs, unsigned int locationId){
        rs->installAttribute(locationId, bufferId, size, type, isNormalized,0,0); 
      };

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

