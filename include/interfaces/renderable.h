#pragma once
#include <vector>
#include "attribute_provider.h"
#include "uniform_provider.h"
#include "RenderUnit.h"
#include "../common/utils.hpp"

namespace mpr {
  struct Renderable:UniformProvider {
    virtual void addPassUnit(RenderUnit) = 0;
    virtual std::vector<RenderUnit> getUnits() = 0;
    virtual ~Renderable() {} ;
  };
}
