#pragma once
#include "../Material.h"

namespace mpr{
  class MaterialProvider{
    public:
      MaterialProvider(){};
      virtual ~MaterialProvider(){};
      virtual std::shared_ptr<Material> getMaterial() =0;
      virtual std::unordered_map<std::string, uint16_t> getLocations() =0;
  };
}
