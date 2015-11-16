#pragma once
#include <unordered_map>
#include <memory>
#include "./RenderSystem.hpp"
#include "../uniform_installers.hpp"

namespace mpr{

  class Uniform{
    protected:
      Uniform(){};
    public:
      virtual void set(std::shared_ptr<RenderSystem> rs, unsigned int location)=0;
      virtual ~Uniform(){};
  };

  template<class T>
  class UniformValue:public Uniform{
    private:
      UniformValue();
      const T value;
    public:
      explicit UniformValue(T v):value(v) {}
      virtual void set(std::shared_ptr<RenderSystem>, unsigned int location) {
        uniformInstaller(location, value);
      }
  };


  typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
}
