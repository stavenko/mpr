#pragma once
#include <vector>
#include "../common/Attribute.h"


namespace mpr{
  struct AttributeProvider{
    AttributeProvider(){};
    virtual ~AttributeProvider(){};
    virtual std::vector<std::string> attributeNames() = 0;
    virtual std::shared_ptr<Attribute> getAttributeLocation(std::string attributeName) = 0;
    private:
      AttributeProvider(AttributeProvider &ap);
      AttributeProvider &operator=(AttributeProvider &ap);
  };
}


