#pragma once 
#include "../interfaces/RenderSystem.hpp"
#include "../Input.h"

#ifndef __APPLE_CC__
  #include <GL/glew.h>
#else
  #include <OpenGL/gl3.h>
  #include <OpenGL/glext.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>

namespace mpr{
  class OpenGL final :public RenderSystem{
    int samples;
    int glfwVersionMajor;
    int glfwVersionMinor;
    int width;
    int height;
    bool isFullScreen;
    bool doCreateWindow;
    bool glewInitialized;
    GLFWwindow *window;
    std::string title;
    unsigned int vertexArrayId;

    public:
      virtual unsigned int createBuffer(size_t size, const void* ptr) {
        std::cout << "create buffer\n";
        unsigned int bufferId;
        glGenBuffers(1, &bufferId); 
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW);
        return bufferId;
      }

      virtual void deleteBuffer(unsigned int id){
        glDeleteBuffers(1, &id);
      }

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
        glfwVersionMajor(4), 
        glfwVersionMinor(6),
        width(640), height(480),
        isFullScreen(false), doCreateWindow(true),
        window(nullptr),
        glewInitialized(false),
        title("Default title") 
      {
          initGLFW();
      }
   
      virtual ~OpenGL(){
        if(window) glfwDestroyWindow(window);
        glDeleteVertexArrays(1, &vertexArrayId);
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

      void glew(){
#ifndef __APPLE__        
        if(!glewInitialized){
          glewExperimental=GL_TRUE;
          GLenum err = glewInit();
          if (err != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            return;
          }
          fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
          glewInitialized = true;
        }
#endif

      }
      void determineMaxAvailableVersion(){
        for (int max=glfwVersionMajor;max!=0;--max){
          if(max < glfwVersionMajor) glfwVersionMinor = 9;
          for(int min=glfwVersionMinor; min != 0; --min) {

            std::cout << "Try: " << max <<"."<< min << "\n";
            glfwWindowHint(GLFW_SAMPLES, samples);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
            //if(glfwVersionMajor * 10 + glfwVersionMinor > 32)
              glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor); 
            if(isFullScreen) 
              window = glfwCreateWindow(mode->width, 
                mode->height, title.c_str(), monitor, NULL);
            else
              window = glfwCreateWindow(width, height, title.c_str(),NULL,NULL);
            if(!window) continue;

            glfwMakeContextCurrent(window);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
            glfwVersionMajor = max;
            glfwVersionMinor = min;
            return;

          }
        }
      }

      void initGLFW(){
        std::cout << "init GLFW\n";

        if(!glfwInit()){
          this->errorCallback(100501, "GLFW didn't initialized");
          exit( EXIT_FAILURE );
        }
        if (!doCreateWindow) 
          glfwWindowHint(GLFW_VISIBLE, false);
        glfwSetErrorCallback(this->errorCallback);
        determineMaxAvailableVersion();
        glew();
        std::cout << "Inited window\n";
        
        glGenVertexArrays(1, &vertexArrayId);
        std::cout << "GEN ARRAYS BIND\n";

        glBindVertexArray(vertexArrayId);
        std::cout << "DONE\n";
      }

      static void errorCallback(int error, const char *description){
        std::cerr << "[Error] " << error << " (" << description << ")\n";
      }
  };
}
