#pragma once
#include <memory>
#include "OpenGL.hpp"

namespace mpr{
  static void kc(GLFWwindow * win, int k, int s, int a, int m){
    std::cout<<"SSS"<<std::endl;
  } 
  template<>
  class Input<OpenGL>{

    OpenGL *openglInstance;
    std::function<void(int,int,int,int)> key;
    std::function<void()> onClose_;

    Input():
      openglInstance(nullptr),
      key([](int,int,int,int){}),
      onClose_([](){})
    {};
    Input(Input const&);

    static void keyCallback(GLFWwindow* window, 
                            int key, int scancode, int action, int mode) {
      std::cout << "Static" << std::endl;
      instance().key(key,scancode, action, mode); 
    }
    static void windowCloseCallback(GLFWwindow *window){
      std::cout << "Close me\n";
      instance().onClose_();
    }

    public:
      
      static Input &instance() {
        static Input instance;

        return instance;
      }

      Input &setRenderSystem(std::shared_ptr<RenderSystem> r){
        openglInstance = static_cast<OpenGL*>(r.get());
        std::cout << "set REN "<< openglInstance->getWindow() << "\n"; 

        if(!glfwSetKeyCallback(openglInstance->getWindow(), this->keyCallback)){
          std::cerr << "key callback didn't installed" << std::endl;
        }
        glfwSetWindowCloseCallback(openglInstance->getWindow(), this->windowCloseCallback);

        return *this;
      }

      Input &bindKeys(std::function<void(int,int,int,int)> keyFunc){
        key = keyFunc;
        return *this;
      }
      Input &onClose(std::function<void()> onClose){
         onClose_ = onClose;
         return *this;
      }
  };
}
