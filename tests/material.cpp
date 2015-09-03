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
// Interpolated values from the vertex shaders\n\
varying vec3 fragmentColor;\n\
\n\
void main(){\n\
\n\
        // Output color = color specified in the vertex shader,\n\
        // interpolated between all 3 surrounding vertices\n\
        gl_FragColor = vec4(fragmentColor, 1);\n\
}";

struct RS:public mpr::RenderSystem{
  virtual ~RS(){};
  RS(){};
  virtual void finalizeRenderLoop(){};
};

TEST(materialTest, materialCreationTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(1,1);
}
TEST(materialTest, uniformParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(m.getUniformTypes().size(),2);
}
TEST(materialTest, attributeParseTest){
  std::shared_ptr<mpr::RenderSystem> r(new RS);
  mpr::Material m (r, testVertexShader12, testFragmentShader12);
  ASSERT_EQ(m.getAttributeTypes().size(),2);
}
