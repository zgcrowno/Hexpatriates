#pragma once

#include "Hexpatriates.h"
#include "Laser.h"
#include "Spawner.h"

namespace hexpatriates
{
    class LaserTeleportable : public Laser
    {
    protected:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on object separation
        virtual orxBOOL OnSeparate(ScrollObject *_poCollider);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        bool m_bHasCreatedPortal;
        Spawner *m_gun;
    };
}
