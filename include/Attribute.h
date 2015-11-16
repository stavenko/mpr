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
    size_t perElement;
    size_t elements;
    uint16_t type;
    bool isNormalized;
    std::weak_ptr<RenderSystem> renderer;

    public:

      template<typename T>
      explicit Attribute(
        std::weak_ptr<RenderSystem> r, 
        std::vector<T> &input,
        size_t pe,
        bool in = false
      ):bufferId(-1), isNormalized(in), renderer(r), elements(input.size()), perElement(pe){
        std::shared_ptr<RenderSystem> rs(r);
        bufferId = rs->createBuffer(input.size() * sizeof(T), &input[0]);
        type = rs->getItemType<T>();
      }

      void set(std::shared_ptr<RenderSystem> rs, unsigned int locationId){
        rs->installAttribute(locationId, bufferId, perElement, type, isNormalized,0,0); 
      };

      size_t size(){ return elements; }

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

