#include "attribute_provider.h"
#include "uniform_provider.h"
#include "material_provider.h"

namespace mpr{
  class RenderUnit:
    public MaterialProvider, 
    public UniformProvider, 
    public AttributeProvider{

  };
}
