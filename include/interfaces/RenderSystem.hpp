#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

namespace mpr {

  template<typename T>
  struct tpChooser{
    static uint16_t type(){ return -1; }
  };

class RenderSystem {
 public:
  RenderSystem() {}
  virtual ~RenderSystem() {};
  virtual void finalizeRenderLoop() = 0;
  virtual unsigned int createProgram(const std::string, const std::string) = 0;
  virtual void disposeProgram(unsigned int const) = 0;
  virtual void setProgram(unsigned int const) = 0;
  virtual unsigned int createBuffer(size_t, const void*) = 0;
  virtual void deleteBuffer(unsigned int) = 0;
  virtual unsigned int getUniformLocation(unsigned int, const std::string&) = 0;
  virtual unsigned int getAttributeLocation(unsigned int,
                                            const std::string&) = 0;
  virtual unsigned int installAttribute(uint32_t location, uint32_t buffer,
                                        uint16_t size, uint32_t type, bool isNormalized,
                                        uint16_t stride, void* ptr) = 0;
  virtual void viewport() = 0;
  template<typename T>
    uint16_t getItemType(){
      std::cout << "GOOD\n";
      return tpChooser<T>::type();
    }
};


}
