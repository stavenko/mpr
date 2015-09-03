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
      virtual unsigned int createProgram(std::string const vShader, 
                                         std::string const fShader){
        unsigned int vsId = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fsId = glCreateShader(GL_FRAGMENT_SHADER);

        char const *vsSrcPtr = vShader.c_str();
        glShaderSource(vsId, 1, &vsSrcPtr, NULL);
        glCompileShader(vsId);

        int InfoLogLength = 0;
        int Result = 0;

        glGetShaderiv(vsId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
          std::string vertexShaderErrorMessage;
          glGetShaderInfoLog(vsId, InfoLogLength, NULL, &vertexShaderErrorMessage[0]);
          std::cout << vertexShaderErrorMessage << "\n";
        }

        char const *fsSrcPtr = fShader.c_str();
        glShaderSource(fsId, 1, &fsSrcPtr, NULL);
        glCompileShader(fsId);

        glGetShaderiv(fsId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
          std::string fragmentShaderErrorMessage;
          glGetShaderInfoLog(fsId, InfoLogLength, NULL, &fragmentShaderErrorMessage[0]);
          std::cout << fragmentShaderErrorMessage << "\n";
        }

        unsigned int programId = glCreateProgram();
        glAttachShader(programId, vsId);
        glAttachShader(programId, fsId);
        glLinkProgram(programId);

        glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
          std::string programErrorMessage;
          glGetProgramInfoLog(programId, InfoLogLength, NULL, &programErrorMessage[0]);
          std::cout << programErrorMessage << "\n";
        }


        glDeleteShader(vsId);
        glDeleteShader(fsId);
        return programId;
      }
      void disposeProgram(unsigned int programId){
        glDeleteProgram(programId);
      }
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
