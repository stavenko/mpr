#ifndef GL_UNIFORM_H
#define GL_UNIFORM_H
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

void uniform(unsigned int l, glm::vec3 &v){
  std::cout << "Vec 3" << v.x << "\n";
}

void uniform(unsigned int l, glm::mat4 &m){
  std::cout << "Mat 3" << m[0].x << "\n";
}

#endif
