#include <string>
#include <gtest/gtest.h>
#include "Material.h"
#include "interfaces/RenderSystem.hpp"

std::string testVertexShader12 = "#version 120\n\
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
std::string testFragmentShader12 = "#version 120\n\
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

std::string testVertexShader33 ="#version 330 core\n\
\n\
// Input vertex data, different for all executions of this shader.\n\
layout(location = 0) in vec3 vertexPosition_modelspace;\n\
layout(location = 1) in vec2 vertexUV;\n\
\n\
// Output data ; will be interpolated for each fragment.\n\
out vec2 UV;\n\
\n\
// Values that stay constant for the whole mesh.\n\
uniform mat4 MVP;\n\
\n\
void main(){\n\
\n\
        // Output position of the vertex, in clip space : MVP * position\n\
        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n\
\n\
        // UV of the vertex. No special space for this one.\n\
        UV = vertexUV;\n\
}";


std::string testFragmentShader33 = "#version 330 core\n\
\n\
// Interpolated values from the vertex shaders\n\
in vec2 UV;\n\
\n\
// Ouput data\n\
out vec3 color;\n\
\n\
// Values that stay constant for the whole mesh.\n\
uniform sampler2D myTextureSampler;\n\
\n\
void main(){\n\
\n\
        // Output color = color of the texture at the specified UV\n\
        color = texture2D( myTextureSampler, UV ).rgb;\n\
}\n\
";



struct RS:public mpr::RenderSystem{
  virtual ~RS(){};
  RS(){};
  virtual void finalizeRenderLoop(){};
  virtual unsigned int createProgram(std::string const v, std::string const f){
    return 1;
  }
  virtual void deleteBuffer(unsigned int) {}
  virtual unsigned int createBuffer(size_t, const void*){return 1;}
  virtual unsigned int getUniformLocation(unsigned int, const std::string&){}
  virtual unsigned int getAttributeLocation(unsigned int, const std::string&){}
  virtual void disposeProgram(unsigned int) { }
  virtual void setProgram(unsigned int) { }
  virtual void viewport() { }
  virtual unsigned int installAttribute(uint32_t location, uint32_t buffer,
                                        uint16_t size, uint32_t type, bool isNormalized,
                                        uint16_t stride, void* ptr) {}
};

TEST(materialTest, materialCreationTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(1,1);
}
TEST(materialTest, uniformParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(m.getUniformTypes().size(),3);
}
TEST(materialTest, attributeParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(m.getAttributeTypes().size(),2);
}
TEST(materialTest, modernAttributeParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader33, testFragmentShader33);
  ASSERT_EQ(m.getAttributeTypes().size(),2);
}
TEST(materialTest, mordernUniformParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader33, testFragmentShader33);
  ASSERT_EQ(m.getUniformTypes().size(),2);
}
