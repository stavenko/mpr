#pragma once 
#include "../interfaces/RenderSystem.hpp"
#include "../Input.h"

#include <GLFW/glfw3.h>

namespace mpr{
  class OpenGL final :public RenderSystem{
    int samples;
    int glfwVersionMajor;
    int glfwVersionMinor;
    int width;
    int height;
    bool isFullScreen;
    bool doCreateWindow;
    GLFWwindow *window;
    std::string title;

    public:
      OpenGL():
        samples(4), 
        glfwVersionMajor(3), 
        glfwVersionMinor(3),
        width(640), height(480),
        isFullScreen(false), doCreateWindow(true),
        window(nullptr),
        title("Default title") {
        initGLFW();
      }
   
      virtual ~OpenGL(){
        if(window) glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "destructor called" << std::endl;
      }
      virtual void finalizeRenderLoop(){
        glfwSwapBuffers(window);
        glfwPollEvents();
      }
     friend class Input<OpenGL>;
    private:
      GLFWwindow *getWindow(){
        return window;
      }
      void createWindow(){
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor); 
        if(isFullScreen) 
          window = glfwCreateWindow(mode->width, 
            mode->height, title.c_str(), monitor, NULL);
        else
          window = glfwCreateWindow(width, height, title.c_str(),NULL,NULL);

        if(!window) {
          glfwTerminate();
          this->errorCallback(100500, "Window cannot be created");
          exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
      }

      void initGLFW(){
        if(!glfwInit()){
          this->errorCallback(100501, "GLFW didn't initialized");
          exit( EXIT_FAILURE );
        }
        glfwSetErrorCallback(this->errorCallback);
        
        glfwWindowHint(GLFW_SAMPLES, samples);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwVersionMinor);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        if(glfwVersionMajor * 10 + glfwVersionMinor > 32)
          glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if(doCreateWindow) createWindow();
      }

      static void errorCallback(int error, const char *description){
        std::cerr << "Error: " << error << " (" << description << ")\n";
      }
  };
}
