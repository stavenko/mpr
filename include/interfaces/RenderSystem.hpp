#pragma once
#include <unordered_map>
#include <string>
#include <vector>

namespace mpr{
  class RenderSystem {
    public:
      RenderSystem() {}
      virtual ~RenderSystem() {} ;
      virtual void finalizeRenderLoop() = 0;
      virtual unsigned int createProgram(const std::string, 
                                         const std::string) = 0;
      virtual void disposeProgram(unsigned int const) = 0;
      virtual void setProgram(unsigned int const) = 0;
      virtual unsigned int createBuffer(size_t, const void*) = 0;
      virtual void deleteBuffer(unsigned int) =0;
      virtual unsigned int getUniformLocation(unsigned int, const std::string&) =0;
      virtual unsigned int getAttributeLocation(unsigned int, const std::string&) =0;
      virtual void viewport()=0;
  };
}
