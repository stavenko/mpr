#include <iostream> 
#include "renderables/mesh.hpp"
#include "gl/OpenGL.hpp"
#include "Material.h"
#include "Context.h"
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
  mpr::Context ctx(openGL);
  ctx.add(passOpt);
  ctx.add(mesh);

  ctx.render();
  std::cout << "Go on" << "\n";
  return 1; 
}
