#pragma once
#include <unordered_map>
#include <memory>

namespace mpr{

  class Uniform{
    private:
      Uniform();
    public:
      virtual void setup(unsigned int location);
  };

  template<class T>
  class UniformValue:public Uniform{
    private:
      UniformValue();
      const T value;
    public:
      explicit UniformValue(T &v):value(v) {}
      virtual void setup(unsigned int location) {
        glUniformCall(location, value);
      }
  };


  typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
}
