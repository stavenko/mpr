#pragma once
#include "../Material.h"

namespace mpr{
  using ::std::string;
  using ::std::unordered_map;
  using ::std::shared_ptr;
  class MaterialProvider{
    public:
      MaterialProvider(){};
      virtual ~MaterialProvider(){};
      virtual shared_ptr<Material> getMaterial() =0;
      virtual const unordered_map<string, unsigned int> &getUniformLocations() =0;
      virtual const unordered_map<string, unsigned int > &getAttributeLocations() =0;
  };
}
