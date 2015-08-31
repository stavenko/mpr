#pragma once
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

  void glUniformCall( unsigned int location, float value){
    std::cout << "float value" << value << " \n";
  }
}
