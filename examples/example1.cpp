#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderables/mesh.hpp"
#include "gl/OpenGL.hpp"
#include "gl/Input.h"
#include "Material.h"
#include "Context.h"
#include "Texture.h"
#include "ContextRenderer.hpp"
#include "interfaces/Uniform.h"

static std::string testVertexShader12 =
    "#version 410\n\
\n\
// Input vertex data, different for all executions of this shader.\n\
layout(location=0) in vec3 position;\n\
layout(location=1) in vec2 uvcoords;\n\
// layout(location=1) in vec3 vertexColor;\n\
\n\
// Output data ; will be interpolated for each fragment.\n\
out vec3 fragmentColor;\n\
out vec2 uv;\n\
// Values that stay constant for the whole mesh.\n\
uniform mat4 MVP;\n\
\n\
void main(){\n\
\n\
        // Output position of the vertex, in clip space : MVP * position\n\
        gl_Position =  MVP * vec4(position,1);\n\
\n\
        // The color of each vertex will be interpolated\n\
        // to produce the color of each fragment\n\
        fragmentColor = vec3(1,0,0);\n\
        uv = uvcoords;\n\
}";
static std::string testFragmentShader12 =
    "#version 410\n\
\n\
// uniform sampler2D tex;\n\
uniform vec2 ppos;\n\
// Interpolated values from the vertex shaders\n\
in vec3 fragmentColor;\n\
in vec2 uv;\n\
out vec4 color;\n\
\n\
void main(){\n\
\n\
        // Output color = color specified in the vertex shader,\n\
        // interpolated between all 3 surrounding vertices\n\
        // vec4 someColor= texture(tex, uv);\n\
        color = vec4(uv, 0, 1) ;\n\
}";
static const GLfloat g_uv_buffer_data[] = {
   0.000059f, 1.0f-0.000004f,
   0.000103f, 1.0f-0.336048f,
   0.335973f, 1.0f-0.335903f,
   1.000023f, 1.0f-0.000013f,
   0.667979f, 1.0f-0.335851f,
   0.999958f, 1.0f-0.336064f,
   0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
static const GLfloat g_vertex_buffer_data[] =  { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};


std::string filePath = "/home/vstavenko/Downloads/plu1rss1.jpg";
int main(int argc, char **args) {

  int vertexDataSize = sizeof(g_vertex_buffer_data) / sizeof(GLfloat);
  std::vector<float> buffer; // (vertexDataSize);
  std::vector<float> uvs; // (vertexDataSize);
  
  for (int i = 0; i < vertexDataSize ; ++i) {
    buffer.push_back(g_vertex_buffer_data[i]);
  }
  vertexDataSize = sizeof(g_uv_buffer_data) / sizeof(GLfloat);

  for (int i = 0; i < vertexDataSize; ++i) {
    uvs.push_back(g_uv_buffer_data[i]);
  }

      

  std::shared_ptr<mpr::RenderSystem> openGL(new mpr::OpenGL());
  //mpr::Texture tex(openGL, "/home/vstavenko/projects/ogl/tutorial05_textured_cube/uvtemplate.bmp");

  std::shared_ptr<mpr::Attribute> attributePtr(
      new mpr::Attribute(openGL, buffer, 3));

  std::shared_ptr<mpr::Attribute> uvAttribute(
      new mpr::Attribute(openGL, uvs, 2));
  std::shared_ptr<mpr::Mesh> mesh(new mpr::Mesh);
  std::shared_ptr<mpr::Material> material(
      new mpr::Material(openGL, testVertexShader12, testFragmentShader12));
  mpr::Pass passOpt("MAIN", mpr::MAIN);
  auto uniforms = mpr::Uniforms();
  auto projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.01f, 100.0f);
  auto view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
  auto model = glm::mat4(1.f);

  std::shared_ptr<mpr::Uniform>  mvp(new mpr::UniformValue<glm::mat4>(projection * view * model));
  std::shared_ptr<mpr::Uniform>  v2p(new mpr::UniformValue<glm::vec2>(glm::vec2()));
  uniforms.emplace( "MVP", mvp );
  uniforms.emplace( "ppos", v2p );

  mpr::RenderUnit pass0(material, uniforms, mpr::Attributes(), "MAIN");
  pass0.setAttributesDrawType(GL_TRIANGLES);
  pass0.install("position", attributePtr);
  pass0.install("uvcoords", uvAttribute);
  pass0.setAttributePointAmount(buffer.size());
  mesh->addPassUnit(pass0);
  mpr::Context ctx;
  ctx.add(passOpt);
  ctx.add(mesh);

  bool shoudClose = false;

  mpr::Input<mpr::OpenGL>::instance()
      .setRenderSystem(openGL)
      .onClose([&shoudClose]() { shoudClose = true; })
      .bindKeys([&](int key, int scancode, int action,
                    int mode) { std::cout << "Dymanic\n"; });

  mpr::ContextRenderer ctxR(openGL);

  while (!shoudClose) {

    ctxR.render(ctx);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  std::cout << "Go on"
            << "\n";
  return 1;
}
