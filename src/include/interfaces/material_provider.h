#include "../Material.h"

namespace mpr{
  class MaterialProvider{
    public:
      MaterialProvider(){};
      virtual ~MaterialProvider() = 0;
      virtual std::shared_ptr<Material> getMaterial() =0;
  };
}
