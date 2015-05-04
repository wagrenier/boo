#ifndef CGENERICPAD_HPP
#define CGENERICPAD_HPP

#include "CDeviceBase.hpp"

namespace boo
{

class CGenericPad final : public CDeviceBase
{
public:
    CGenericPad(CDeviceToken* token);
    ~CGenericPad();

    void deviceDisconnected();
};

}

#endif // CGENERICPAD_HPP