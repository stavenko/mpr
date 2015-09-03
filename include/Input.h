#pragma once
namespace mpr{
  template<typename T>
  class Input{
    private:
      Input(){};
      Input(Input const&);
    public:
      Input &instance(T t){
        static Input instance;
        return instance;
      }
  };
}
