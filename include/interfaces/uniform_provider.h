#pragma once
#include <boost/optional.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Uniform.h"

namespace mpr {
struct UniformProvider {
  virtual ~UniformProvider() {};
  virtual std::vector<std::string> uniformNames() = 0;
  virtual std::shared_ptr<Uniform> getUniformValue(std::string uniformName) = 0;
  virtual const Uniforms allUniforms() = 0;
  virtual const boost::optional<std::shared_ptr<Uniform>> findUniform(
      const std::string) = 0;
  UniformProvider() {};

 private:
  UniformProvider(UniformProvider &up);
  UniformProvider &operator=(UniformProvider &up);
};
}
