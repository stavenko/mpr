#pragma once
#include "attribute_provider.h"
#include "uniform_provider.h"
#include "RenderablePass.h"

namespace mpr {
  struct Renderable:UniformProvider {
    virtual void addPass(RenderablePass rp) = 0;
    virtual ~Renderable() {} ;
  };
}
