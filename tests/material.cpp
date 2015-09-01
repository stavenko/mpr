#include <gtest/gtest.h>
#include "../src/include/Material.h"
#include "../src/include/interfaces/RendererInitializer.hpp"

std::string testVertexShader = "#version 120\
\
// Input vertex data, different for all executions of this shader.\
attribute vec3 vertexPosition_modelspace;\
attribute vec3 vertexColor;\
\
// Output data ; will be interpolated for each fragment.\
varying vec3 fragmentColor;\
// Values that stay constant for the whole mesh.\
uniform mat4 MVP;\
\
void main(){\
\
        // Output position of the vertex, in clip space : MVP * position\
        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\
\
        // The color of each vertex will be interpolated\
        // to produce the color of each fragment\
        fragmentColor = vertexColor;\
}";
std::string testFragmentShader = "#version 120\
\
uniform sampler2D texture;\
// Interpolated values from the vertex shaders\
varying vec3 fragmentColor;\
\
void main(){\
\
        // Output color = color specified in the vertex shader,\
        // interpolated between all 3 surrounding vertices\
        gl_FragColor = vec4(fragmentColor, 1);\
}";

TEST(materialTest, materialCreationTest){
  std::shared_ptr<mpr::RendererInitializer> r(new mpr::RendererInitializer);
  mpr::Material m (r, testVertexShader, testFragmentShader);
  ASSERT_EQ(1,1);
}
TEST(materialTest, uniformParseTest){
  std::shared_ptr<mpr::RendererInitializer> r(new mpr::RendererInitializer);
  mpr::Material m (r, testVertexShader, testFragmentShader);
  ASSERT_EQ(m.getUniformTypes().size(),2);
}
TEST(materialTest, attributeParseTest){
  std::shared_ptr<mpr::RendererInitializer> r(new mpr::RendererInitializer);
  mpr::Material m (r, testVertexShader, testFragmentShader);
  ASSERT_EQ(m.getAttributeTypes().size(),2);
}
