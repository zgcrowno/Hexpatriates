#pragma once

#include "Hexpatriates.h"

namespace hexpatriates
{
    class RaycastData
    {
    public:
        orxVECTOR m_hitPosition;
        orxVECTOR m_hitNormal;
        orxOBJECT *m_hitObject;

        RaycastData(orxOBJECT *_hitObject, orxVECTOR _hitPosition, orxVECTOR _hitNormal);
        ~RaycastData();
    };
}
