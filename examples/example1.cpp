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
    "vertexShader ", 
    "fragmentShader"
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
