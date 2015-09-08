#pragma once
#include <vector>
#include "../Attribute.h"


namespace mpr{
  struct AttributeProvider{
    AttributeProvider(){};
    virtual ~AttributeProvider(){};
    virtual std::vector<std::string> attributeNames() = 0;
    virtual const Attributes allAttributes() = 0;
    virtual std::shared_ptr<Attribute> getAttributeLocation(std::string attributeName) = 0;
    virtual void set(const std::string, const std::shared_ptr<Attribute>) = 0;
    private:
      AttributeProvider(AttributeProvider &ap);
      AttributeProvider &operator=(AttributeProvider &ap);
  };
}


