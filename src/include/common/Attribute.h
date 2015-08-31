#pragma once
namespace mpr{
  struct Attribute{
    unsigned int location; // GL location of a buffer;
    unsigned char size; // number of compenents (vec2 or vec3);
    unsigned char componentSize; // e.g size of float;
  };
}

