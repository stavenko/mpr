#pragma once
#include <boost/optional.hpp>
#include <vector>
#include "../Attribute.h"

namespace mpr{
  struct AttributeProvider{
    AttributeProvider(){};
    virtual ~AttributeProvider(){};
    virtual std::vector<std::string> attributeNames() = 0;
    virtual const Attributes allAttributes() = 0;
    virtual std::shared_ptr<Attribute> getAttributeLocation(std::string attributeName) = 0;
    virtual void setAttributesDrawType(uint16_t) = 0;
    virtual uint16_t getAttributesDrawType() = 0;
    virtual void setAttributePointAmount(uint32_t) = 0;
    virtual uint32_t getAttributePointAmount() = 0;

    virtual void install(const std::string, const std::shared_ptr<Attribute>) = 0;
    virtual const boost::optional<std::shared_ptr<Attribute>> 
      findAttribute(const std::string) = 0;
    private:
      AttributeProvider(AttributeProvider &ap);
      AttributeProvider &operator=(AttributeProvider &ap);
  };
}

