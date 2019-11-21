#pragma once

#include "Hexpatriates.h"
#include "Projectile.h"

namespace hexpatriates
{
    class TetheredProjectile : public Projectile
    {
    protected:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete() = 0;
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal) = 0;
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        orxOBJECT *m_parentGun;
    };
}
