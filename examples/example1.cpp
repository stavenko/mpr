#include <iostream> 
#include <chrono>
#include <thread>
#include "renderables/mesh.hpp"
#include "gl/OpenGL.hpp"
#include "gl/Input.h"
#include "Material.h"
#include "Context.h"
#include "ContextRenderer.hpp"
#include "interfaces/Uniform.h"

int main(int argc, char **args){
  std::shared_ptr<mpr::RenderSystem> 
    openGL(new mpr::OpenGL());
  std::shared_ptr<mpr::Mesh> mesh(new mpr::Mesh);
  std::shared_ptr<mpr::Material> material(new mpr::Material(
    openGL,
    "vertexShader ", 
    "fragmentShader"
  ));
  mpr::Pass passOpt("MAIN", mpr::MAIN);
  mpr::RenderUnit pass0(material, mpr::Uniforms(), mpr::Attributes(), "MAIN");
  mesh->addPassUnit(pass0);
  mpr::Context ctx;
  ctx.add(passOpt);
  ctx.add(mesh);

  bool shoudClose = false;

  mpr::Input<mpr::OpenGL>::instance()
    .setRenderSystem(openGL)
    .onClose([&shoudClose]() { shoudClose = true; });
    .bindKeys([&](int key, int scancode, int action, int mode){
      std::cout << "Dymanic\n";
    })

  mpr::ContextRenderer ctxR(openGL);

  while(!shoudClose){

    ctxR.render(ctx);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  std::cout << "Go on" << "\n";
  return 1; 
}
