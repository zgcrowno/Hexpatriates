#pragma once

#include "Hexpatriates.h"
#include "Projectile.h"
#include "Spawner.h"

namespace hexpatriates
{
    class Turret : public Projectile
    {
    private:
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
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        bool m_bIsAttached;
        float m_movementDirection;
        Spawner *m_turretGun;
    };
}
