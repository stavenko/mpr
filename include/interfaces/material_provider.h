#pragma once
#include "../Material.h"

namespace mpr{
  class MaterialProvider{
    public:
      MaterialProvider(){};
      virtual ~MaterialProvider(){};
      virtual std::shared_ptr<Material> getMaterial() =0;
  };
}
