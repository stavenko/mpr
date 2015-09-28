#include <iostream> 
#include <chrono>
#include <thread>
#include <array>
#include "renderables/mesh.hpp"
#include "gl/OpenGL.hpp"
#include "gl/Input.h"
#include "Material.h"
#include "Context.h"
#include "ContextRenderer.hpp"
#include "interfaces/Uniform.h"

static std::string testVertexShader12 = "#version 120\n\
\n\
// Input vertex data, different for all executions of this shader.\n\
attribute vec3 vertexPosition_modelspace;\n\
attribute vec3 vertexColor;\n\
\n\
// Output data ; will be interpolated for each fragment.\n\
varying vec3 fragmentColor;\n\
// Values that stay constant for the whole mesh.\n\
uniform mat4 MVP;\n\
\n\
void main(){\n\
\n\
        // Output position of the vertex, in clip space : MVP * position\n\
        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n\
\n\
        // The color of each vertex will be interpolated\n\
        // to produce the color of each fragment\n\
        fragmentColor = vertexColor;\n\
}";
static std::string testFragmentShader12 = "#version \n\
\n\
uniform sampler2D texture;\n\
uniform vec2 ppos;\n\
// Interpolated values from the vertex shaders\n\
varying vec3 fragmentColor;\n\
\n\
void main(){\n\
\n\
        // Output color = color specified in the vertex shader,\n\
        // interpolated between all 3 surrounding vertices\n\
        gl_FragColor = vec4(fragmentColor, 1);\n\
}";
static const GLfloat g_vertex_buffer_data[][3] = { 
  {-1.0f,-1.0f,-1.0f}, 
  {-1.0f,-1.0f, 1.0f}, 
  {-1.0f, 1.0f, 1.0f}, 
  {1.0f, 1.0f, -1.0f}, 
  {-1.0f,-1.0f,-1.0f}, 
  {-1.0f, 1.0f,-1.0f}, 
  {1.0f,-1.0f , 1.0f}, 
  {-1.0f,-1.0f,-1.0f}, 
  {1.0f,-1.0f ,-1.0f}, 
  {1.0f, 1.0f ,-1.0f}, 
  {1.0f,-1.0f ,-1.0f}, 
  {-1.0f,-1.0f,-1.0f}, 
  {-1.0f,-1.0f,-1.0f}, 
  {-1.0f, 1.0f, 1.0f}, 
  {-1.0f, 1.0f,-1.0f}, 
  {1.0f,-1.0f , 1.0f}, 
  {-1.0f,-1.0f, 1.0f}, 
  {-1.0f,-1.0f,-1.0f}, 
  {-1.0f, 1.0f, 1.0f}, 
  {-1.0f,-1.0f, 1.0f}, 
  {1.0f,-1.0f , 1.0f}, 
  {1.0f, 1.0f , 1.0f}, 
  {1.0f,-1.0f ,-1.0f}, 
  {1.0f, 1.0f ,-1.0f}, 
  {1.0f,-1.0f ,-1.0f}, 
  {1.0f, 1.0f , 1.0f}, 
  {1.0f,-1.0f , 1.0f}, 
  {1.0f, 1.0f , 1.0f}, 
  {1.0f, 1.0f ,-1.0f}, 
  {-1.0f, 1.0f,-1.0f}, 
  {1.0f, 1.0f , 1.0f}, 
  {-1.0f, 1.0f,-1.0f}, 
  {-1.0f, 1.0f, 1.0f}, 
  {1.0f, 1.0f , 1.0f}, 
  {-1.0f, 1.0f, 1.0f}, 
  {1.0f,-1.0f , 1.0f} 
};

int main(int argc, char **args){
  int vertexDataSize = sizeof(g_vertex_buffer_data) / sizeof(GLfloat);
  std::cout << "S:" << vertexDataSize / 3 << "\n";
  std::vector<std::array<float,3>> buffer(vertexDataSize / 3);
  for(int i =0; i < vertexDataSize / 3; ++i) {
    std::array<float,3> v{g_vertex_buffer_data[i][0],
                          g_vertex_buffer_data[i][1],
                          g_vertex_buffer_data[i][2]};
    buffer.push_back(v);
  }

  std::shared_ptr<mpr::RenderSystem> 
    openGL(new mpr::OpenGL());
  std::shared_ptr<mpr::Attribute> attributePtr(new mpr::Attribute(openGL, buffer));
  std::shared_ptr<mpr::Mesh> mesh(new mpr::Mesh);
  std::shared_ptr<mpr::Material> material(new mpr::Material(
    openGL,
    testVertexShader12,
    testFragmentShader12 
  ));
  mpr::Pass passOpt("MAIN", mpr::MAIN);
  mpr::RenderUnit pass0(material, mpr::Uniforms(), mpr::Attributes(), "MAIN");
  pass0.set("vertices", attributePtr);
  mesh->addPassUnit(pass0);
  mpr::Context ctx;
  ctx.add(passOpt);
  ctx.add(mesh);

  bool shoudClose = false;

  mpr::Input<mpr::OpenGL>::instance()
    .setRenderSystem(openGL)
    .onClose([&shoudClose]() { shoudClose = true; })
    .bindKeys([&](int key, int scancode, int action, int mode){
      std::cout << "Dymanic\n";
    });

  mpr::ContextRenderer ctxR(openGL);

  while(!shoudClose){

    ctxR.render(ctx);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  std::cout << "Go on" << "\n";
  return 1; 
}
