#pragma once
#include <iostream>
#include <glm/glm.hpp>
namespace mpr{
  void uniformInstaller( unsigned int location, const glm::vec2 &value);
  void uniformInstaller( unsigned int location, const glm::mat4 &value);
  void uniformInstaller( unsigned int location, const float &value);
}

