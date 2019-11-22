#ifndef I_BUILDER
#define I_BUILDER

#include <sstream>


struct IBuilder{
    virtual void build(std::stringstream&) = 0;
    virtual ~IBuilder() = default;
};

#endif
