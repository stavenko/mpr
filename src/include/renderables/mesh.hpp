#include "interfaces/renderable.h"
#include "../common/utils.hpp"

namespace mpr{
  class Mesh final:public Renderable{
    typedef std::unordered_map<std::string, std::shared_ptr<Uniform>> Uniforms;
    private:
      Uniforms uniforms;
      std::vector<RenderablePass> renderablePasses;
    public:
      Mesh(){
        std::cout << "create mesh\n";
      };
      virtual ~Mesh(){
        std::cout << "destroy mesh\n";
      }
      virtual void addPass(RenderablePass rp) {
        std::cout << "Add pass\n";
      };
      virtual std::vector<std::string> uniformNames(){
        return keys(uniforms);
      }
      virtual std::shared_ptr<Uniform> getUniformValue(std::string name){
        return uniforms[name];
      }
  };

}
