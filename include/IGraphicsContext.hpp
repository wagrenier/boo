#ifndef IGRAPHICSCONTEXT_HPP
#define IGRAPHICSCONTEXT_HPP

#include <string>

namespace boo
{

class IGraphicsContext
{
public:
    virtual ~IGraphicsContext() {}

    virtual void setMinVersion  (const int& min)=0;
    virtual void setMajorVersion(const int& maj)=0;
    virtual bool create()=0;
    virtual const std::string version() const=0;
    virtual const std::string name() const=0;
    virtual int depthSize() const=0;
    virtual int redDepth() const=0;
    virtual int greenDepth() const=0;
    virtual int blueDepth() const=0;
};

}

#endif // IGRAPHICSCONTEXT_HPP