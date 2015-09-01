#include "interfaces/renderable.h"
#include "interfaces/RenderUnit.h"
#include "../common/utils.hpp"

namespace mpr{
  class Mesh final:public Renderable{
    private:
      Uniforms uniforms;
      std::vector<RenderUnit> renderUnits;
    public:
      Mesh(){
        std::cout << "create mesh\n";
      };
      virtual ~Mesh(){
        std::cout << "destroy mesh\n";
      }
      virtual void addPassUnit(RenderUnit ru) {
        std::cout << "Add pass\n";
        renderUnits.push_back(ru);
      };
      virtual std::vector<RenderUnit> getUnits(){
        return renderUnits;
      }
      virtual std::vector<std::string> uniformNames(){
        return keys(uniforms);
      }
      virtual std::shared_ptr<Uniform> getUniformValue(std::string name){
        return uniforms[name];
      }
      virtual const Uniforms allUniforms(){
        return uniforms;
      }
  };

}
